#include "UIButton.h"
#include "UIImage.h"
#include "macro.h"

UIButton::UIButton(sf::Vector2f size) : UIElement(size), _backgroundImage(new UIImage(_size))
{
	_backgroundImage->SetParent(*this);
}

UIButton::UIButton(UIElement& parent, sf::Vector2f size, std::string& name) : UIElement(parent, size, name), _backgroundImage(new UIImage(_size))
{
	_backgroundImage->SetParent(*this);
}

UIButton::~UIButton()
{
	DELETE_PTR(_backgroundImage);
}

void UIButton::SetPosition(float positionX, float positionY)
{
	UIElement::SetPosition(positionX, positionY);
	if(_backgroundImage)
	{
		_backgroundImage->SetPosition(0, 0);
	}
}

void UIButton::SetScale(float scaleX, float scaleY)
{
	UIElement::SetScale(scaleX, scaleY);
	if(_backgroundImage)
	{
		_backgroundImage->SetScale(scaleX, scaleY);
		_size = _backgroundImage->GetSpriteSize();
	}
}

void UIButton::Draw(sf::RenderWindow& window) const
{
	if(_backgroundImage)
	{
		_backgroundImage->Draw(window);
	}
}

void UIButton::SetBackgroundColor(sf::Color& color) const
{
	if(_backgroundImage)
	{
		_backgroundImage->SetColor(color);
	}
}

void UIButton::SetBackgroundImage(sf::Texture& texture)
{
	if (_backgroundImage)
	{
		_backgroundImage->SetTexture(texture);
		_size = _backgroundImage->GetSpriteSize();
	}
}
