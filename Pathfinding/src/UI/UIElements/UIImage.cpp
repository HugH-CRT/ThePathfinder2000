#include "UIImage.h"

UIImage::UIImage(sf::Vector2f size) : UIElement(size)
{
}

UIImage::UIImage(UIElement& parent, sf::Vector2f size, std::string& name) : UIElement(parent, size, name)
{
}

UIImage::~UIImage()
{
}

void UIImage::SetPosition(float positionX, float positionY)
{
	UIElement::SetPosition(positionX, positionY);
	_sprite.setPosition(_position);
}

void UIImage::SetScale(float scaleX, float scaleY)
{
	UIElement::SetScale(scaleX, scaleY);
	_sprite.setScale(scaleX, scaleY);
	_size = sf::Vector2f(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
}

void UIImage::SetTexture(sf::Texture& texture)
{
	_sprite.setTexture(texture);
	_size.x = _sprite.getGlobalBounds().width;
	_size.y = _sprite.getGlobalBounds().height;
}

void UIImage::SetColor(sf::Color& color)
{
	_sprite.setColor(color);
}

sf::Vector2f UIImage::GetSpriteSize() const
{
	return sf::Vector2f(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
}

void UIImage::Draw(sf::RenderWindow& window) const
{
	window.draw(_sprite);
}

