#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIElement
{
private:
	class UIWidget& m_UIContext;
	float m_width;
	float m_height;
	sf::Vector2f m_scale;
	sf::Vector2f m_position;
	bool m_autoSize = false;

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
	float GetWidth() const;
	void SetHeight(const float height);
	float GetHeight() const;
	void SetAutoSize(const bool autoSize);

	void SetTexture(sf::Texture& texture, bool contentSize = false);
	void SetPosition(float positionX, float positionY);
	void SetScale(float sizeX, float sizeY);

	sf::Sprite m_sprite;
};