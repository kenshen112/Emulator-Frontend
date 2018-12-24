#include "systems.h"

Systems::Systems() {}

void Systems::listDirectory(int i) {
  int num = 0;
  if ((dirToOpen = opendir(systems[i]->romLocation.c_str())) != NULL) {
    while ((dirData = readdir(dirToOpen)) != NULL) {
      std::cout << num << ": " << dirData->d_name << std::endl;
      num++;
    }
  }
}

void Systems::regexString(std::string path, std::regex reg) 
{
  std::sregex_iterator match(path.begin(), path.end(), reg);
  std::sregex_iterator endIt;
  while(match != endIt)
  {

  }
}

void Systems::systemSelect() {

  parseSettings();
  std::cout << "What System: ";
  std::cin >> systemName;
  listDirectory(systemName);
  int size;
  std::cout << "What Game: ";
  std::cin.ignore();
  std::getline(std::cin, romName);
  openProgram(systemName);
}

void Systems::parseSettings() {
  fin.open("/home/kenshen/Projects/Frontend/Data/Systems.json");

  if (fin.fail()) {
    std::cerr << "fin fialed bitch" << std::endl;
    return;
  }

  settings = json::parse(fin);

  Console *listSystem = new Console;
  for (auto &consoles : settings) {
    listSystem->platform = consoles["SystemName"].get<std::string>() + '\0';
    listSystem->romLocation = consoles["RomPath"].get<std::string>() + '\0';
    listSystem->executeable = {
        consoles["Executeable"].get<std::string>() + '\0', NULL};
    listSystem->arguments = consoles["Args"].get<std::string>();
    systems.push_back(listSystem);
  }

  std::cout << "Name: " << systems[0]->executeable << std::endl;
  std::cout << "Rom: " << systems[0]->romLocation << std::endl;
  fin.close();
  fin.clear();
}

// Args are off, it's working otherwise
void Systems::openProgram(int i) {
  pid_t pid;
  pid_t parent;
  std::string fullPath = systems[i]->romLocation + romName + '\0';
  std::cout << "Path: " << fullPath << std::endl;

  isExecuteable[0] = new char[systems[i]->executeable.size()];
  strncpy(isExecuteable[0], systems[i]->executeable.c_str(),
          systems[i]->executeable.size());
  isExecuteable[1] = new char[systems[i]->arguments.size()];
  strncpy(isExecuteable[1], systems[i]->arguments.c_str(),
          systems[i]->arguments.size());
  isExecuteable[2] = new char[systems[i]->romLocation.size()];
  strncpy(isExecuteable[2], systems[i]->romLocation.c_str(),
          systems[i]->romLocation.size());
            
  strncat(isExecuteable[2], "\\", sizeof("\\"));
  strncat(isExecuteable[2], romName.c_str(), romName.size());

  isExecuteable[3] = NULL;

  std::cout << "Path: " << isExecuteable[0] << isExecuteable[1]
            << isExecuteable[2] << std::endl;

  parent = getpid();
  pid = fork();

  if (pid < 0) {
    std::cerr << "fork failed" << std::endl;
    exit(1);
  }

  else if (pid > 0) {
    waitpid(pid, 0, 0);
  }

  else if (pid == 0) {

    if ((execvp(isExecuteable[0], isExecuteable)) < 0) {
      std::cerr << "Execution failed: " << strerror(errno) << std::endl;
      exit(1);
    }
  }
}

Systems::~Systems() {}