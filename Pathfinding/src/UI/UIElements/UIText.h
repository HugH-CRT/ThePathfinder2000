#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "UI/UIElement.h"
#include "SFML/Graphics/Text.hpp"
#include <string>

class UIText : public UIElement
{
public:
	explicit UIText(sf::Vector2f size);
	UIText(UIElement& parent, sf::Vector2f size, std::string& name);

	virtual ~UIText() override;
	void Draw(sf::RenderWindow& window) const override;
	void SetPosition(float positionX, float positionY) override;
	void SetScale(float scaleX, float scaleY) override;

	void SetString(std::string text);
	void SetFontSize(unsigned size);
	void SetFont(sf::Font& font);

protected:
	sf::Text _text;
};

#endif /* UI_TEXT_H */
