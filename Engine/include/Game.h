#pragma once
#include <memory>
#include <Engine.h>

namespace Engine {

	class Game
	{
	public:
		virtual ~Game() = default;
		virtual EngineConfig config() const { return {}; }
		
		virtual void setup(Runtime&) {}
		
		//virtual std::unique_ptr<Level> create_first_level() = 0; // only put when we have a level class
	};
	
}

std::unique_ptr<Engine::Game> create_game();