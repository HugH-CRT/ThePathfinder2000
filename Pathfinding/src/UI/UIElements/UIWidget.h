/**
* @file UIWidget.h
*
* @brief
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include "UI/UIElement.h"
#include "Game.h"

class UIWidget : public UIElement
{
public:
	GameDataRef _gameDataRef;

	explicit UIWidget(sf::Vector2f size, GameDataRef& gameDataRef);
	explicit UIWidget(UIElement& parent, sf::Vector2f size, std::string& name);

	~UIWidget() override;
	void Draw(sf::RenderWindow& window) const override;

	template<typename Element>
	Element* addElement(std::string nameElement) 
	{
		if (!std::is_base_of<UIElement, Element>()) 
		{
			return nullptr;
		}

		Element* element = new Element(*this, _size, nameElement);
		_childElements.push_back(element);
		return element;
	}

	void HandleEvents(sf::Event& event, sf::RenderWindow& window) override;

private:
	std::vector<UIElement*> _childElements;
};
#endif /* UI_WIDGET_H */