//BS"D
#include <fstream>
#include "Controller.h"

int main()
{
    std::ofstream err("log.txt", std::ofstream::out);
    try 
    {
        Controller c;
        c.run();
    }
    catch(std::string s){
        err << s;
        err.close();
    }
    catch (...) 
    { 
        err << "Error!\n";
        err.close();
    }
    return 0;
}

