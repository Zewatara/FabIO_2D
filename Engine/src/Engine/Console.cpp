#include <iostream>
#include "Engine/Console.h"

namespace Engine
{
    Console::Console()
    {
        std::cout << colorConsole <<"FabIO_2D Engine -- Console started" << colorDefaultLB;
    }

    Console::~Console()
    {
        std::cout << colorConsole << "FabIO_2D Engine -- Console stopping" << colorDefaultLB;
    }

    void Console::Warning(const std::string& input)
    {
        std::cout << colorWarning << "[Warning]: " << input << colorDefaultLB;
    }

    void Console::Error(const std::string& input)
    {
        std::cout << colorError << "[Error]: " << input << colorDefaultLB;
    }
}