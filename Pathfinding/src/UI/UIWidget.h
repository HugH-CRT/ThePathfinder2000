#pragma once
#include "UIElements/UIElement.h"
#include "Game.h"
#include <vector>
#include <SFML/Graphics.hpp>

class UIWidget
{
private:
	int m_width;
	int m_height;
	std::vector<UIElement*> m_elements;
	GameDataRef m_data;

public:
	UIWidget(const int width, const int height, const GameDataRef& dataRef);
	virtual ~UIWidget();

	virtual void draw(sf::RenderWindow& window) = 0;

	GameDataRef GetGameDataRef() const;

	template<typename Element>
	Element* addElement(std::string nameElement) {
		if (!std::is_base_of<UIElement, Element>()) {
			return nullptr;
		}
		
		Element* element = new Element(*this, nameElement);
		m_elements.push_back(element);
		return element;
	}
};