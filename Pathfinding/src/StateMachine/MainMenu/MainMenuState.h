/**
* @file MainMenuState.h
*
* @brief Main menu screen of the game
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/

#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

/**
* @class MainMenuState
* @brief  Main menu screen of the game
*/
class MainMenuState final : public State
{
public: 
	explicit MainMenuState(GameDataRef data);
	~MainMenuState() override;

	/* Implementation of State class */
	
	void Draw(float dt) override;
	void HandleInput() override;
	void Init() override;
	void LoadTextures() override;
	void LoadFonts() override {}
	void SetTexts() override{}
	void SetTextures() override;
	void Update(float dt) override;
	void SetScales() override;
	void SetPositions() override;

	/* Implementation of State class */

private: 
		
	GameDataRef _data;
	std::unique_ptr<class UIWidget> _MainMenuWidget;
	
	sf::Sprite _background;
	sf::Sprite playButton;
	sf::Sprite title;
};

#endif /* MAIN_MENU_STATE_H */