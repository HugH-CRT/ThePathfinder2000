#include "UIButton.h"
#include "UIText.h"

UIButton::UIButton(UIWidget& uiContext) : UIElement(uiContext)
{
}

UIButton::UIButton(UIWidget& uiContext, std::string name) : UIElement(uiContext, name)
{
}

UIButton::~UIButton()
{
	if (m_textButton != nullptr) {
		delete m_textButton;
		m_textButton = nullptr;
	}
}

void UIButton::Draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

void UIButton::SetText(std::string text)
{
	m_textButton->SetText(text);
}

UIText* UIButton::AddUIText(std::string text)
{
	m_textButton = new UIText(GetWidgetContext(), text);
	return m_textButton;
}

UIText& UIButton::GetUIText() const
{
	return *m_textButton;
}
