#include "UIButton.h"
// #include "UIElements/UI_Image/UIImage.h"

UIButton::UIButton(sf::Vector2f size) : UIElement(size), _backgroundImage(std::make_unique<UIImage>(size))
{
	_backgroundImage->SetParent(this);
}

UIButton::UIButton(UIElement* parent, sf::Vector2f size, std::string& name) 
	: UIElement(parent, size, name)
	, _backgroundImage(std::make_unique<UIImage>(size))
{
	_backgroundImage->SetParent(this);
}

UIButton::~UIButton()
{
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

void UIButton::HandleEvents(sf::Event& event, sf::RenderWindow& window)
{
	sf::IntRect tempRect(_position.x, _position.y, _size.x, _size.y);
	if (tempRect.contains(sf::Mouse::getPosition(window)))
	{
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code)
		{
			if(OnClickEvent)
			{
				OnClickEvent();
			}
		}

		if(!_isHover && OnHoverEvent)
		{
			_isHover = true;
			OnHoverEvent();
		}

	}else if(_isHover&& OnUnHoverEvent)
	{
		_isHover = false;
		OnUnHoverEvent();
	}
}
