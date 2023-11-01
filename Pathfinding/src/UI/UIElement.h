#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class UIElement
{
public:
	sf::Vector2f _size;
	sf::Vector2f _position;
	sf::Vector2f _scale;

	UIElement* _parentElement = nullptr;
	std::string _name;

public:
	explicit UIElement(sf::Vector2f size);
	UIElement(UIElement& parent, sf::Vector2f size, std::string& name);
	virtual ~UIElement();

	virtual void Draw(sf::RenderWindow& window) const = 0;

	virtual void SetPosition(float positionX, float positionY);
	virtual void SetScale(float scaleX, float scaleY);
};

#endif /* UI_ELEMENT_H */