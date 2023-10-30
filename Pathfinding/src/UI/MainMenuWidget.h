#pragma once
#include "UIWidget.h"

class MainMenuWidget : public UIWidget
{
public:
	MainMenuWidget(const int width, const int height, const GameDataRef& dataRef);

	virtual ~MainMenuWidget();

	virtual void draw(sf::RenderWindow& window) override;

};