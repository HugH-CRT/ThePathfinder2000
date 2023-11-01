#pragma once
#include "UIElement.h"

class UIButton : public UIElement
{
private:
	class UIText* m_textButton = nullptr;
	class UIImage* m_backgroundImage = nullptr;

public:
	explicit UIButton(UIWidget& uiContext);
	UIButton(UIWidget& uiContext, std::string name);

	virtual ~UIButton();

	virtual void Draw(sf::RenderWindow& window) const override;

	void SetText(std::string text);
	void SetBackgroundImage(sf::Texture& texture);

	virtual void SetPosition(float positionX, float positionY) override;

	class UIText* AddUIText(std::string text = "");
	class UIText& GetUIText() const;
};