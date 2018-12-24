#ifndef SYSTEMS_H
#define SYSTEMS_H
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <wait.h>
#include <regex>
#include "json.hpp"
#include <fstream>
#include <string.h>
#include <vector>
#include <errno.h>

using json = nlohmann::json;

enum list{PLAYSTATION1, PLAYSTATION2, SNES};

struct Console
{
    std::string platform;
    std::string executeable;
    std::string arguments;
    std::string romLocation;
};

extern int errno;

class Systems
{

private:
    int systemName;
    std::string romName;
    std::ifstream fin;
    json settings;

    std::vector <Console*> systems;

    DIR *dirToOpen;
    struct dirent *dirData;
    int pipeList[3];
    char *isExecuteable[4];

public:
    Systems();
    void systemSelect();
    void parseSettings();
    void regexString(std::string path, std::regex reg);
    void listDirectory(int i);
    void openProgram(int i);
    ~Systems();
};

#endif /* SYSTEMS_H */
