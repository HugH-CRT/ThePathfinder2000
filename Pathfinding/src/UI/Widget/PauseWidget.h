#ifndef PAUSE_WIDGET_H
#define PAUSE_WIDGET_H

#include "UI/UIElements/UIWidget.h"

class PauseWidget : public UIWidget
{
public:
	PauseWidget(sf::Vector2f size, GameDataRef& gameDataRef);
	PauseWidget(UIElement& parent, sf::Vector2f size, std::string& name);

	virtual ~PauseWidget() override;
};

#endif /* PAUSE_WIDGET_H */
