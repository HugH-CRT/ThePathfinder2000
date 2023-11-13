#include "UI/UIElements/UICheckbox.h"

UICheckbox::UICheckbox(sf::Vector2f size) : UIElement(size), _text(std::make_unique<UIText>(_size)), _sprite(std::make_unique<UIImage>(_size))
{
}

UICheckbox::UICheckbox(UIElement& parent, sf::Vector2f size, std::string& name) : UIElement(parent, size, name), _text(std::make_unique<UIText>(_size)), _sprite(std::make_unique<UIImage>(_size))
{
}

UICheckbox::~UICheckbox()
{
}

void UICheckbox::Init(sf::Texture& uncheckedTexture, sf::Texture& checkedTexture, std::string text, sf::Font& font)
{
	_text->SetParent(*this);
	_text->SetFont(font);
	_text->SetString(text);

	_sprite->SetParent(*this);
	InitTexture(uncheckedTexture, checkedTexture);
}

void UICheckbox::InitTexture(sf::Texture& uncheckedTexture, sf::Texture& checkedTexture)
{
	_uncheckedTexture = uncheckedTexture;
	_checkedTexture = checkedTexture;

	if(_sprite)
	{
		_sprite->SetTexture(_uncheckedTexture);
		_sprite->SetScale(0.1f, 0.1f);

	}

	sf::Vector2f newSize{ 0,0 };
	if (_text)
	{
		newSize += sf::Vector2f(_text->_size.x, _text->_size.y);
	}

	if (_sprite)
	{
		newSize += _sprite->GetSpriteSize();
	}

	_size = newSize;
}

UIText& UICheckbox::GetText() const
{
	if(_text)
	{
		return *_text;
	}
}

UIImage& UICheckbox::GetSprite() const
{
	if(_sprite)
	{
		return *_sprite;
	}
}

void UICheckbox::SetPosition(float positionX, float positionY)
{
	UIElement::SetPosition(positionX, positionY);
	if(_text)
	{
		_text->SetPosition(positionX, positionY);
	}

	if(_sprite)
	{
		_sprite->SetPosition(_text->_size.x + 10.f, 0);
	}
}

void UICheckbox::SetScale(float scaleX, float scaleY)
{
	UIElement::SetScale(scaleX, scaleY);
	sf::Vector2f newSize{ 0,0 };
	if(_text)
	{
		_text->SetScale(scaleX, scaleY);
		newSize += sf::Vector2f(_text->_size.x, _text->_size.y);
	}

	if(_sprite)
	{
		_sprite->SetScale(scaleX, scaleY);
		newSize += _sprite->GetSpriteSize();
	}

	_size = newSize;
}

void UICheckbox::Draw(sf::RenderWindow& window) const
{
	if (_sprite)
	{
		_sprite->Draw(window);
	}
	if(_text)
	{
		_text->Draw(window);
	}

	
}

void UICheckbox::HandleEvents(sf::Event& event, sf::RenderWindow& window)
{
	sf::IntRect tempRect(_position.x, _position.y, _size.x, _size.y);
	if (tempRect.contains(sf::Mouse::getPosition(window)))
	{
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code)
		{
			SwitchState();

			if (OnClickEvent)
			{
				OnClickEvent();
			}
		}
	}
}

void UICheckbox::SwitchState()
{
	_isChecked = !_isChecked;
	if(_isChecked)
	{
		_sprite->SwitchTexture(_checkedTexture);
	}else
	{
		_sprite->SwitchTexture(_uncheckedTexture);
	}
}
