/**
* @file GameWidget.h
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

#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include "Widget/UIWidget.h"

class GameWidget : public UIWidget
{
public:
	GameWidget(sf::Vector2f size, GameDataRef& gameDataRef);
	GameWidget(UIElement* parent, sf::Vector2f size, std::string& name);

	~GameWidget() override;
};

#endif /* GAME_WDIGET_H */