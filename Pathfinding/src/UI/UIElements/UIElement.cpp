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

void UIElement::SetHeight(const float height)
{
	m_height = height;
}