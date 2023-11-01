#include "UIElement.h"
#include <SFML/Graphics/Sprite.hpp>
#include "UIElement.h"

UIElement::UIElement(sf::Vector2f size) : _size(size), _position(0, 0), _parentElement(nullptr), _scale(1.f,1.f)
{
}

UIElement::UIElement(UIElement& parent, sf::Vector2f size, std::string& name) : _parentElement(&parent), _size(size), _name(name), _position(0,0), _scale(1.f, 1.f)
{
}

UIElement::~UIElement()
{	
}

void UIElement::SetPosition(float positionX, float positionY)
{
	sf::Vector2f parentPosition{ 0,0 };
	sf::Vector2f parentSize{ 0, 0 };
	if (&_parentElement) {
		parentPosition = _parentElement->_position;
		parentSize = _parentElement->_size;
	}

	_position = sf::Vector2f(parentPosition.x + positionX, parentPosition.y + positionY);
}

void UIElement::SetScale(float scaleX, float scaleY)
{
	sf::Vector2f parentSize{ 0, 0 };
	if (&_parentElement) {
		parentSize = _parentElement->_size;
	}
	_scale = sf::Vector2f(scaleX, scaleY);
	_size = sf::Vector2f(parentSize.x + (_size.x * _scale.x), parentSize.y + (_size.y * _scale.y));
}
