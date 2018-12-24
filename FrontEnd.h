#ifndef FRONTEND_H
#define FRONTEND_H
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include "json.hpp"
#include <fstream>
#include <string>
#include <vector>


using json = nlohmann::json;

struct Console
{
    std::string platform;
    std::string executeable;
    std::string arguments;
    std::string romLocation;
};


class FrontEnd
{
private:
    int systemName;
    std::string romName;
    std::ifstream fin;
    json settings;

    std::vector <Console*> systems;

    DIR *dirToOpen;
    struct dirent *dirData;

public:
    FrontEnd();
    void systemSelect();
    void parseSettings();
    void listDirectory(int i);
    void openProgram(int i);
    ~FrontEnd();
};


#endif /* FRONTEND_H */