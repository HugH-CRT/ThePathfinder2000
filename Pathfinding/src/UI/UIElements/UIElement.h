#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIElement
{
private:
	class UIWidget& m_UIContext;
	float m_width;
	float m_height;

protected:
	std::string m_name;

public:
	explicit UIElement(UIWidget& uiContext);
	UIElement(UIWidget& uiContext, std::string name);
	virtual ~UIElement();

	virtual void Draw(sf::RenderWindow& window) const = 0;
	UIWidget& GetWidgetContext() const;
	std::string GetName() const { return m_name; }

	void SetWidth(const float width);
	void SetHeight(const float height);

	sf::Sprite m_sprite;
};