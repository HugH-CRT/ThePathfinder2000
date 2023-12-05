#include "UITextField.h"

#include <iostream>

UITextField::UITextField(sf::Vector2f size, unsigned int maxChars)
	: UIElement(size)
	, _size(maxChars)
	, _rect(sf::Vector2f(2.f, 2.f))
	, _hasFocus(false)
{
	this->Init();
}

UITextField::UITextField(UIElement* parent, sf::Vector2f size, std::string& name, unsigned int maxChars)
	: UIElement(parent, size, name)
	, _size(maxChars)
	, _rect(size)
	, _hasFocus(false)
{
	this->Init();
}

UITextField::~UITextField()
{
}

void UITextField::Draw(sf::RenderWindow& window) const
{
	window.draw(_rect);
	window.draw(_drawText);
}

void UITextField::SetPosition(float positionX, float positionY)
{
	UIElement::SetPosition(positionX, positionY);
	_rect.setPosition(positionX, positionY);
	_drawText.setPosition(positionX +5, positionY +5);
}

void UITextField::SetScale(float scaleX, float scaleY)
{
	UIElement::SetScale(scaleX, scaleY);
	_rect.setScale(scaleX, scaleY);
	_drawText.setScale(scaleX, scaleY);
}

void UITextField::SetFont(sf::Font& font)
{
	_drawText.setFont(font);
}

std::string UITextField::GetText() const
{
	return _text;
}

void UITextField::HandleEvents(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed) 
	{
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		_hasFocus = _rect.getGlobalBounds().contains(mousePos);
	}

	if (event.type == sf::Event::TextEntered && _hasFocus) 
	{
		if (event.text.unicode == 8 && !_text.empty()) 
		{ 
			_text.pop_back();
		}
		else if (event.text.unicode < 128) 
		{
			_text += static_cast<char>(event.text.unicode);
			std::cout << " t : " << _text << "\n"; 
		}
		
		_drawText.setString(_text);
	}

}

void UITextField::Init(void)
{
	_rect.setFillColor(sf::Color::White);
	_rect.setOutlineThickness(2.f);
	_rect.setOutlineColor(sf::Color::Black);

	_drawText.setCharacterSize(150);
	_drawText.setFillColor(sf::Color::Black);
}
