#include <Engine/Runtime.h>
#include <Engine.h>
#include <SDL3/SDL.h>


namespace Engine
{
    Runtime::Runtime(const EngineConfig& params)
    : mainWindow(params.window)
    {
    }
    
    int Runtime::Run()
    {
        Uint64 last = SDL_GetPerformanceCounter();
        const double freq = static_cast<double>(SDL_GetPerformanceFrequency());

        while (!mainWindow.shouldClose() && !quitRequested)
        {
            const Uint64 now = SDL_GetPerformanceCounter();
            Time.delta = static_cast<float>(static_cast<double>(now - last) / freq);
            Time.elapsed += Time.delta;
            Time.frame++;
            last = now;

            mainWindow.pollEvents();

            // Aqui é o loop principal da engine (o main esta no EntryPoint.cpp
            
            // Futuramente level->update(Time.delta) etc
            
            // o level é q tem o update e o fixed update etc e chama essa funçao a cada ojecto criado no jogo.
            // ou seija o lvl vai ter uma funçao "spawn" pra criar objectos e dps vai adicionalos a uma lista
            // dps cada jogo vai ter o seu lvl a ser puchada desta classe tipo shootergamelevel q la vai se 
            // cirar os objectos q ja tao na cena tipo o player

            mainWindow.swapBuffers();
        }

        return 0;
    }

}