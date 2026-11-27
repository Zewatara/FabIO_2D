add_library(Engine STATIC
    src/Engine.cpp
    src/Graphics/Window.cpp
    src/Core/Runtime.cpp
    src/EntryPoint.cpp
    src/Engine/Console.cpp
)
add_library(Engine::Engine ALIAS Engine)

# Public include dir: games write #include <Engine/Engine.h>
target_include_directories(Engine PUBLIC include)

# PUBLIC so anything linking Engine also gets SDL3, GL, Box2D and GLM
target_link_libraries(Engine
    PUBLIC
        SDL3::SDL3
        glad
        OpenGL::GL
        box2d
        glm::glm
)

if(MSVC)
    target_compile_options(Engine PRIVATE /W4)
else()
    target_compile_options(Engine PRIVATE -Wall -Wextra)
endif()
