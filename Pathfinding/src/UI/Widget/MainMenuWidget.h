#ifndef MAIN_MENU_WIDGET_H
#define MAIN_MENU_WIDGET_H

#include "UI/UIElements/UIWidget.h"

class MainMenuWidget : public UIWidget
{
public:
	MainMenuWidget(sf::Vector2f size, GameDataRef& gameDataRef);
	MainMenuWidget(UIElement& parent, sf::Vector2f size, std::string& name);

	virtual ~MainMenuWidget() override;

	void StartGame();
};

#endif /* MAIN_MENU_WIDGET_H */
