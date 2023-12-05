/**
* @file UIText.h
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

#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "UIElements/UIElement.h"
#include "SFML/Graphics/Text.hpp"
#include <string>

class UIText : public UIElement
{
public:
	explicit UIText(sf::Vector2f size);
	explicit UIText(UIElement* parent, sf::Vector2f size, std::string& name);

	~UIText() override;

	void Draw(sf::RenderWindow& window) const override;
	void SetPosition(float positionX, float positionY) override;
	void SetScale(float scaleX, float scaleY) override;

	void SetString(std::string& text);
	void SetFontSize(unsigned size);
	void SetFont(sf::Font& font);

protected:
	sf::Text _text;
};

#endif /* UI_TEXT_H */
