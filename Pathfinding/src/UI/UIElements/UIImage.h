#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#include "UI\UIElement.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>

class UIImage : public UIElement
{
public:
	explicit UIImage(sf::Vector2f size);
	UIImage(UIElement& parent, sf::Vector2f size, std::string& name);

	virtual ~UIImage() override;

	virtual void SetPosition(float positionX, float positionY) override;
	virtual void SetScale(float scaleX, float scaleY) override;
	virtual void Draw(sf::RenderWindow& window) const override;

	void SetTexture(sf::Texture& texture);
	void SetColor(sf::Color& color);
private:
	sf::Sprite _sprite;
	sf::Color _imageColor;
};

#endif /* UI_IMAGE_H */