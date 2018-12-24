#include "FrontEnd.h"

FrontEnd::FrontEnd()
{

}

void FrontEnd::listDirectory(int i)
{
   int num = 0;
   if((dirToOpen = opendir(systems[i]->romLocation.c_str())) != NULL)
   {
        while ((dirData = readdir(dirToOpen)) != NULL)
        {
            std::cout << num << ": " << dirData->d_name << std::endl;
            num++;
        }
   }
}

void FrontEnd::systemSelect()
{    
    parseSettings();
    std::cout << "What System: ";
    std::cin >> systemName;
    listDirectory(systemName);
    std::cout << "What Game: ";
    std::cin >> romName;
}

void FrontEnd::parseSettings()
{
    fin.open("Systems.json");
    settings.parse(fin);
    int i = 0;
    systems[i] = new Console;
    systems[i]->platform = settings["SystemName"].get<std::string>();
    systems[i]->romLocation = settings["RomPath"].get<std::string>();
    systems[i]->executeable = settings["Executeable"].get<std::string>();

    i++;
}


void FrontEnd::openProgram(int i)
{
    execl(systems[i]->executeable.c_str(), romName.c_str(), (char *) 0);
}


FrontEnd::~FrontEnd()
{

}