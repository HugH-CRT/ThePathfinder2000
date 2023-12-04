/**
* @file PauseWidget.h
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

#ifndef PAUSE_WIDGET_H
#define PAUSE_WIDGET_H

#include "UI/UIElements/UIWidget.h"

class PauseWidget : public UIWidget
{
public:
	PauseWidget(sf::Vector2f size, GameDataRef& gameDataRef);
	PauseWidget(UIElement& parent, sf::Vector2f size, std::string& name);

	~PauseWidget() override;
};

#endif /* PAUSE_WIDGET_H */
