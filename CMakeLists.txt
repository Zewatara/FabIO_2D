cmake_minimum_required(VERSION 3.24)

project(GameEngine LANGUAGES C CXX)

# ---------------------------------------------------------------------------
# Global settings
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Box2D 3.x is written in C17
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Everything third-party is built as static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# ---------------------------------------------------------------------------
# Dependencies (downloaded at configure time)
# ---------------------------------------------------------------------------
include(FetchContent)

# SDL3 -- windowing, input and OpenGL context creation
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.16
    GIT_SHALLOW    TRUE
)

# Box2D -- 2D physics (v3.x, C API)
set(BOX2D_SAMPLES     OFF CACHE BOOL "" FORCE)
set(BOX2D_UNIT_TESTS  OFF CACHE BOOL "" FORCE)
set(BOX2D_BENCHMARKS  OFF CACHE BOOL "" FORCE)
set(BOX2D_DOCS        OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG        v3.1.1
    GIT_SHALLOW    TRUE
)

# GLM -- header-only math library
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(SDL3 box2d glm)

# GLAD -- OpenGL 3.3 core function loader (pre-generated, lives in external/)
add_subdirectory(external/glad)

# OpenGL -- provided by the operating system / graphics driver
find_package(OpenGL REQUIRED)

# ---------------------------------------------------------------------------
# Our code
# ---------------------------------------------------------------------------
add_subdirectory(Engine)
add_subdirectory(Game)

# Make Game the default target in Visual Studio (F5)
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)

# ---------------------------------------------------------------------------
# Tidy the IDE tree: hide third-party targets in a folder
# ---------------------------------------------------------------------------
foreach(t glad box2d SDL3-static SDL_uclibc)
    if(TARGET ${t})
        set_target_properties(${t} PROPERTIES FOLDER "external")
    endif()
endforeach()
