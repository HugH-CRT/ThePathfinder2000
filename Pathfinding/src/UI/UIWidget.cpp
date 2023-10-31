#include "UIWidget.h"
#include "UIElements/UIElement.h"

UIWidget::UIWidget(const int width, const int height, const GameDataRef& dataRef) : m_width(width), m_height(height), m_data(dataRef)
{
}

UIWidget::~UIWidget()
{
	for (const UIElement* element : m_elements) {
		delete element;
		element = nullptr;
	}
}

void UIWidget::draw(sf::RenderWindow& window)
{
	for (const UIElement* element : m_elements) {
		element->Draw(window);
	}
}

GameDataRef UIWidget::GetGameDataRef() const
{
	return m_data;
}

int UIWidget::GetWidth() const
{
	return m_width;
}

int UIWidget::GetHeight() const
{
	return m_height;
}
