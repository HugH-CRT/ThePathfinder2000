#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include "UI/UIElements/UIWidget.h"

class GameWidget : public UIWidget
{
public:
	GameWidget(sf::Vector2f size, GameDataRef& gameDataRef);
	GameWidget(UIElement& parent, sf::Vector2f size, std::string& name);

	~GameWidget() override;
};

#endif /* GAME_WDIGET_H */