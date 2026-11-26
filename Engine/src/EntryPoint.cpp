#include <exception>
#include <iostream>
#include <memory>
#include "Engine.h"
#include "Game.h"

int main()
{
    try
    {
        std::unique_ptr<Engine::Game> game = create_game();
        
        Engine::Runtime runtime{game ->config()};
        
        game->setup(runtime);
        
        // when we have levels setted up its something like runtime.run(game->create_first_level());)
        return runtime.Run();
        
    }
    catch (const std::exception& error)
    {
        std::cerr << "Fatal error: " << error.what() << '\n';
    }
    return 1;
}