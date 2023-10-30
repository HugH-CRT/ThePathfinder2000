#pragma once
#include "UIElement.h"

class UIButton : public UIElement
{
private:
	class UIText* m_textButton = nullptr;

public:
	explicit UIButton(UIWidget& uiContext);
	UIButton(UIWidget& uiContext, std::string name);

	virtual ~UIButton();

	virtual void Draw(sf::RenderWindow& window) const override;

	void SetText(std::string text);

	class UIText* AddUIText(std::string text = "");
	class UIText& GetUIText() const;
};