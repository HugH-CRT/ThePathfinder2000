/**
* @file MainMenuWidget.h
*
* @brief
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/

#ifndef MAIN_MENU_WIDGET_H
#define MAIN_MENU_WIDGET_H

#include "Widget/UIWidget.h"

class MainMenuWidget : public UIWidget
{
public:
	MainMenuWidget(sf::Vector2f size, GameDataRef& gameDataRef);
	MainMenuWidget(UIElement* parent, sf::Vector2f size, std::string& name);

	~MainMenuWidget() override;

	void StartGame();
};

#endif /* MAIN_MENU_WIDGET_H */
