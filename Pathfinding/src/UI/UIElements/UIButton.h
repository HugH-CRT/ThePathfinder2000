#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "UI/UIElement.h"

class UIButton : public UIElement
{
public:
	explicit UIButton(sf::Vector2f size);
	UIButton(UIElement& parent, sf::Vector2f size, std::string& name);

	virtual ~UIButton() override;

	virtual void SetPosition(float positionX, float positionY) override;
	virtual void SetScale(float scaleX, float scaleY) override;
	virtual void Draw(sf::RenderWindow& window) const override;

	void SetBackgroundColor(sf::Color& color) const;
	void SetBackgroundImage(sf::Texture& texture);

private:
	class UIImage* _backgroundImage;
};

#endif /* UI_BUTTON_H */
