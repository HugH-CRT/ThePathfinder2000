#include "UIElement.h"
#include <SFML/Graphics/Sprite.hpp>

UIElement::UIElement(UIWidget& uiContext) : m_UIContext(uiContext)
{
}

UIElement::UIElement(UIWidget& uiContext, std::string name) : m_UIContext(uiContext), m_name(name)
{
}

UIElement::~UIElement()
{
}

UIWidget& UIElement::GetWidgetContext() const
{
	return m_UIContext;
}

void UIElement::SetWidth(const float width)
{
	m_width = width;
}

float UIElement::GetWidth() const
{
	return m_width;
}

void UIElement::SetHeight(const float height)
{
	m_height = height;
}

float UIElement::GetHeight() const
{
	return m_height;
}

void UIElement::SetAutoSize(const bool autoSize)
{
	if (autoSize) {
		m_width = m_sprite.getGlobalBounds().width;
		m_height = m_sprite.getGlobalBounds().height;
		m_autoSize = autoSize;
	}
}

void UIElement::SetTexture(sf::Texture& texture, bool contentSize)
{
	m_sprite.setTexture(texture);
	SetAutoSize(contentSize);
}

void UIElement::SetPosition(float positionX, float positionY)
{
	m_position.x = positionX;
	m_position.y = positionY;
	m_sprite.setPosition(m_position.x, m_position.y);
}

void UIElement::SetScale(float scaleX, float scaleY)
{
	m_scale.x = scaleX;
	m_scale.y = scaleY;
	m_width *= m_scale.x;
	m_height *= m_scale.y;
	m_sprite.scale(m_scale.x, m_scale.y);
}
