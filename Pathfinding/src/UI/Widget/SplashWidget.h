#ifndef SPLASH_WIDGET_H
#define SPLASH_WIDGET_H

#include "UI/UIElements/UIWidget.h"

class SplashWidget : public UIWidget
{
public:
	SplashWidget(const sf::Vector2f& size, GameDataRef& gameDataRef);
	SplashWidget(UIElement& parent, const sf::Vector2f& size, std::string& name);

	~SplashWidget() override;
};

#endif /* SPLASH_WIDGET_H */