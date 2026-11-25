#pragma once

#include <string>

struct SDL_Window;

namespace Engine {

struct ApplicationConfig {
    std::string title = "Game";
    int width  = 1280;
    int height = 720;
    bool vsync = true;
};

// Base class: the Engine owns the window, GL context and main loop.
// A game derives from this and overrides the hooks.
class Application {
public:
    explicit Application(ApplicationConfig config = {});
    virtual ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    // Runs until the window is closed. Returns a process exit code.
    int Run();
    void Quit() { m_running = false; }

protected:
    virtual void OnInit() {}
    virtual void OnUpdate(float /*dt*/) {}   // dt in seconds
    virtual void OnRender() {}
    virtual void OnShutdown() {}

    int Width() const { return m_config.width; }
    int Height() const { return m_config.height; }

private:
    bool Init();
    void Shutdown();

    ApplicationConfig m_config;
    SDL_Window* m_window = nullptr;
    void* m_glContext = nullptr;   // SDL_GLContext
    bool m_running = false;
};

} // namespace Engine
