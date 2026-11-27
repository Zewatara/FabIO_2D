#include <cassert>
#include <iostream>
#include "Engine/Console.h"

namespace
{
    // The console currently owned by the Runtime
    Engine::Console* activeConsole = nullptr;
}

namespace Engine
{
    Console::Console()
    {
        activeConsole = this;
        std::cout << colorEngine <<"FabIO_2D Engine -- Console started" << colorDefaultLB;
    }

    Console::~Console()
    {
        std::cout << colorEngine << "FabIO_2D Engine -- Console stopping" << colorDefaultLB;
        if (activeConsole == this)
            activeConsole = nullptr;
    }

    Console& Console::Get()
    {
        assert(activeConsole && "Console::Get() called before a Runtime was created");
        return *activeConsole;
    }

    void Console::System(const std::string& input)
    {
        std::cout << colorEngine << "[System]: " << input << colorDefaultLB;
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