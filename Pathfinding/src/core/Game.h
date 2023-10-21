#ifndef GAME_H
#define GAME_H

#include "../StateMachine.h"
#include "../AssetManager.h"
#include "../AssetManager.h"
#include "../Managers/InputManager/InputManager.h"

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

struct GameData
{
	StateMachine machine;
	sf::RenderWindow m_window;
	AssetManager m_assetManager;
	InputManager m_inputManager;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
	public : 
		Game(int width, int height, std::string title);

	private : 

		const float frameRate = 1.0f / 60.0f;
		sf::Clock m_clock;

		GameDataRef m_data = std::make_shared<GameData>();

		void Run();	
};

#endif /* GAME_H */