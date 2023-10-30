#pragma once
#include "UIElement.h"
#include <string>
#include <SFML/Graphics/Text.hpp>

class UIText : public UIElement 
{
private:
	sf::Text m_textElement;

public:
	explicit UIText(UIWidget& uiContext);
	UIText(UIWidget& uiContext, std::string name);

	virtual ~UIText();

	virtual void Draw(sf::RenderWindow& window) const override;

	void SetText(std::string text);
	sf::Text GetText() const;
};