add_executable(Game
    src/main.cpp
)

target_link_libraries(Game PRIVATE Engine::Engine)

if(MSVC)
    target_compile_options(Game PRIVATE /W4)
else()
    target_compile_options(Game PRIVATE -Wall -Wextra)
endif()

# Run from the source tree so relative paths (shaders/, assets/) just work
set_target_properties(Game PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY   "${CMAKE_SOURCE_DIR}"
    XCODE_SCHEME_WORKING_DIRECTORY  "${CMAKE_SOURCE_DIR}"
)
