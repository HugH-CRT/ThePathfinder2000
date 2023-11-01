#include "UIWidget.h"
#include "macro.h"
#include "Game.h"

UIWidget::UIWidget(sf::Vector2f size, GameDataRef& gameDataRef) : UIElement(size), _gameDataRef(gameDataRef)
{
}

UIWidget::UIWidget(UIElement& parent, sf::Vector2f size, std::string& name) : UIElement(parent, size, name)
{
}

UIWidget::~UIWidget()
{
	for (UIElement* element : _childElements) {
		DELETE_PTR(element);
	}
}

void UIWidget::Draw(sf::RenderWindow& window) const
{
	for (UIElement* element : _childElements) {
		element->Draw(window);
	}
}
