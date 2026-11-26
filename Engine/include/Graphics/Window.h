#pragma once
#include <memory>

namespace Engine {

    
    //default parameters 
    struct WindowParameters {
        int width = 720;
        int height = 720;
        const char* title = "Game";
        bool vsync = true;
        bool resizable = true;
    };

    class Window {
    public:
        explicit Window(const WindowParameters& desc = {});
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        void pollEvents();
        bool shouldClose() const;
        void swapBuffers();

        int width() const;
        int height() const;
        void setTitle(const char* title);

    private:
        struct Impl;
        std::unique_ptr<Impl> pimpl;
    };
}