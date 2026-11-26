#include <iostream>
#include "Engine/Console.h"

namespace Engine
{
    Console::Console()
    {
        std::cout << "FabIO_2D v000000 -- console started\n";
    }

    Console::~Console()
    {
        std::cout << "FabIO_2D v000000 -- shutting down\n";
    }

    void Console::Log()
    {
        std::cout << "Logging\n";
    }

    void Console::Warning()
    {
        std::cout << "Warning\n";
    }

    void Console::WriteLine()
    {
    	std::cout << "Line\n";
    }

    void Console::Write()
    {
    	std::cout << "Write\n";
    }
}