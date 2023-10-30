#include "UIText.h"
#include "../UIWidget.h"
#include <iostream>

UIText::UIText(UIWidget& uiContext) : UIElement(uiContext)
{
}

UIText::UIText(UIWidget& uiContext, std::string name) : UIElement(uiContext, name)
{
}

UIText::~UIText()
{
}

void UIText::Draw(sf::RenderWindow& window) const
{
	std::cout << "Test UIText drawing" << std::endl;
}

void UIText::SetText(std::string text)
{
	m_textElement.setString(text);
}

sf::Text UIText::GetText() const
{
	return m_textElement;
}

