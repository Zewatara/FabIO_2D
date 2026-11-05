#include <Engine/Application.h>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <cstdio>

namespace Engine {

Application::Application(ApplicationConfig config) : m_config(std::move(config)) {}

Application::~Application() { Shutdown(); }

bool Application::Init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(m_config.title.c_str(), m_config.width, m_config.height,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return false;
    }

    m_glContext = SDL_GL_CreateContext(m_window);
    if (!m_glContext) {
        std::fprintf(stderr, "SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        return false;
    }

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        std::fprintf(stderr, "gladLoadGLLoader failed\n");
        return false;
    }

    SDL_GL_SetSwapInterval(m_config.vsync ? 1 : 0);
    return true;
}

void Application::Shutdown() {
    if (m_glContext) {
        SDL_GL_DestroyContext(static_cast<SDL_GLContext>(m_glContext));
        m_glContext = nullptr;
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
}

int Application::Run() {
    if (!Init()) return 1;

    OnInit();
    m_running = true;
    Uint64 last = SDL_GetPerformanceCounter();
    const double freq = static_cast<double>(SDL_GetPerformanceFrequency());

    while (m_running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) m_running = false;
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) m_running = false;
            if (e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
                m_config.width  = e.window.data1;
                m_config.height = e.window.data2;
                glViewport(0, 0, m_config.width, m_config.height);
            }
        }

        const Uint64 now = SDL_GetPerformanceCounter();
        const float dt = static_cast<float>(static_cast<double>(now - last) / freq);
        last = now;

        OnUpdate(dt);
        OnRender();
        SDL_GL_SwapWindow(m_window);
    }

    OnShutdown();
    return 0;
}

} // namespace Engine
