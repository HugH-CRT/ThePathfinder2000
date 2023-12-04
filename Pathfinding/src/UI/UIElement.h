/**
* @file UIElement.h
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

#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include "UIElement.h"
#include "UI/Events/UIEventListener.h"
#include <SFML/Graphics.hpp>
#include <string>

class UIElement : public UIEventListener
{
public:
	explicit UIElement(sf::Vector2f size);
	explicit UIElement(UIElement& parent, sf::Vector2f size, std::string& name);

	virtual ~UIElement();

	virtual void Draw(sf::RenderWindow& window) const = 0;

	virtual void SetParent(UIElement& parent);
	virtual void SetPosition(float positionX, float positionY);
	virtual void SetScale(float scaleX, float scaleY);
	void HandleEvents(sf::Event& event, sf::RenderWindow& window) override;

	sf::Vector2f _size;
	sf::Vector2f _position;
	sf::Vector2f _scale;

	UIElement* _parentElement = nullptr;
	std::string _name;
};

#endif /* UI_ELEMENT_H */