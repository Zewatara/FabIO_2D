#pragma once
#include <Graphics/Window.h>
#include <Engine/Console.h>
#include <cstdint>

namespace Engine
{
    struct EngineConfig;
    
    struct DeltaTime {
        float delta = 0.0f;
        float fixedDelta = 0.02f;
        double elapsed = 0.0;            // duration of frames passed
        std::uint64_t frame = 0;         // current frame number
    };
    
    class Runtime
    {
    public:
        explicit Runtime(const EngineConfig& params);
        ~Runtime() = default;
        int Run();

        Runtime (const Runtime&) = delete;
        Runtime& operator=(const Runtime&) = delete;
        
        
        void quit() { quitRequested = true; }

        Console& console() { return mainConsole; }
        Window& window() { return mainWindow; }
        const DeltaTime& time() const { return Time; }
        
    protected:
        //virtual void OnInit() {}
        //virtual void OnUpdate(float dt) {}   // dt in seconds
        //virtual void OnRender() {}
        //virtual void OnShutdown() {}
        
        
    private:
        bool Init();
        void Shutdown();
        
        Console mainConsole;
        Window mainWindow;
        bool quitRequested = false;
        DeltaTime Time;
    };
}