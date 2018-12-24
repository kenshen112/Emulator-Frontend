#ifndef FRONTEND_H
#define FRONTEND_H
#include <iostream>
#include <unistd.h>
#include <SDL.h>
#include "systems.h"

class FrontEnd
{
private:
Systems sys;
SDL_Window *frontEndWindow;
public:
    FrontEnd();
    void launch();
    ~FrontEnd();
};


#endif /* FRONTEND_H */