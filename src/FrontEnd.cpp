#include "FrontEnd.h"


FrontEnd::FrontEnd()
{

}

void FrontEnd::launch()
{
    while(true)
    {    
        sys.systemSelect();
    }   
}

FrontEnd::~FrontEnd()
{

}