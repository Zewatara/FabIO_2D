#include <Graphics/Window.h>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <stdexcept>
#include <string>

namespace Engine {

    struct Window::Impl {
        SDL_Window* window = nullptr;
        SDL_GLContext context = nullptr;
        int width = 0;
        int height = 0;
        bool shouldClose = false;

        Impl(const WindowParameters& desc) : width(desc.width), height(desc.height)
        {
            if (!SDL_Init(SDL_INIT_VIDEO)) {
                throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
            }

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            Uint64 flags = SDL_WINDOW_OPENGL;
            
            if (desc.resizable) {
                flags |= SDL_WINDOW_RESIZABLE;
            }

            window = SDL_CreateWindow(desc.title, width, height, flags);
            
            if (!window) {
                SDL_Quit();
                throw std::runtime_error(std::string("Failed to create SDL Window: ") + SDL_GetError());
            }

            context = SDL_GL_CreateContext(window);
            
            if (!context) {
                SDL_DestroyWindow(window);
                SDL_Quit();
                throw std::runtime_error(std::string("Failed to create OpenGL context: ") + SDL_GetError());
            }

            if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
                SDL_GL_DestroyContext(context);
                SDL_DestroyWindow(window);
                SDL_Quit();
                throw std::runtime_error("Failed to initialize GLAD");
            }

            SDL_GL_SetSwapInterval(desc.vsync ? 1 : 0);
        }

        ~Impl()
        {
            if (context) {
                SDL_GL_DestroyContext(context);
            }
            if (window) {
                SDL_DestroyWindow(window);
            }
            SDL_Quit();
        }

        void pollEventsInternal()
        {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    shouldClose = true;
                }
                else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                    width = event.window.data1;
                    height = event.window.data2;
                    glViewport(0, 0, width, height);
                }
            }
        }
        
        
    };

    Window::Window(const WindowParameters& desc) : pimpl{std::make_unique<Impl>(desc)}
    {
    }

    Window::~Window()
    {
    }

    void Window::pollEvents()
    {
        pimpl->pollEventsInternal();
    }

    bool Window::shouldClose() const
    {
        return pimpl->shouldClose;
    }

    void Window::swapBuffers()
    {
        SDL_GL_SwapWindow(pimpl->window);
    }

    int Window::width() const
    {
        return pimpl->width;
    }

    int Window::height() const
    {
        return pimpl->height;
    }

    void Window::setTitle(const char* title)
    {
        SDL_SetWindowTitle(pimpl->window, title);
    }

}