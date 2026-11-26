#include <memory>
#include "Game.h"

namespace
{
    class ShooterGame : public Engine::Game
    {
    public:
        Engine::EngineConfig config() const override
        {
            Engine::EngineConfig config;
            config.window.title = "Shooter Game";
            config.window.width = 800;
            config.window.height = 600;
            config.window.resizable = false;
            return config;
        }

        void setup(Engine::Runtime& runtime) override
        {
            // dar bind aos inputs com o input manager
        }
    };
}

std::unique_ptr<Engine::Game> create_game()
{
    return std::make_unique<ShooterGame>();
}