#include "UIText.h"

UIText::UIText(sf::Vector2f size) 
	: UIElement(size)
{
	SetFontSize(20);
}

UIText::UIText(UIElement* parent, sf::Vector2f size, std::string& name) 
	: UIElement(parent, size, name)
{
	SetFontSize(20);
}

UIText::~UIText()
{
}

void UIText::Draw(sf::RenderWindow& window) const
{
	window.draw(_text);
}

void UIText::SetPosition(float positionX, float positionY)
{
	UIElement::SetPosition(positionX, positionY);
	_text.setPosition(positionX, positionY);
}

void UIText::SetScale(float scaleX, float scaleY)
{
	UIElement::SetScale(scaleX, scaleY);
	_text.setScale(scaleX, scaleY);
	_size = sf::Vector2f(_text.getGlobalBounds().width, _text.getGlobalBounds().height);
}

void UIText::SetString(std::string& text)
{
	_text.setString(text);
	_size = sf::Vector2f(_text.getGlobalBounds().width, _text.getGlobalBounds().height);
}

void UIText::SetFontSize(unsigned size)
{
	_text.setCharacterSize(size);
}

void UIText::SetFont(sf::Font& font)
{
	_text.setFont(font);
}
