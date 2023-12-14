/**
* @file SplashWidget.h
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

#ifndef SPLASH_WIDGET_H
#define SPLASH_WIDGET_H

#include "Widget/UIWidget.h"

class SplashWidget : public UIWidget
{
public:
	SplashWidget(const sf::Vector2f& size, GameDataRef& gameDataRef);
	SplashWidget(UIElement* parent, const sf::Vector2f& size, std::string& name);

	~SplashWidget() override;
};

#endif /* SPLASH_WIDGET_H */