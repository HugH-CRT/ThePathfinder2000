#include "UIButton.h"
#include "UIText.h"
#include "UIImage.h"

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
	}

	if (m_backgroundImage != nullptr) {
		delete m_backgroundImage;
	}
}

void UIButton::Draw(sf::RenderWindow& window) const
{
	if (m_backgroundImage) {
		m_backgroundImage->Draw(window);
	}

	if (m_textButton) {
		m_textButton->Draw(window);
	}
}

void UIButton::SetText(std::string text)
{
	m_textButton->SetText(text);
}

void UIButton::SetBackgroundImage(sf::Texture& texture)
{
	if (m_backgroundImage == nullptr) {
		m_backgroundImage = new UIImage(GetWidgetContext());
		m_backgroundImage->SetImage(texture);
	}
}

void UIButton::SetPosition(float positionX, float positionY)
{
	UIElement::SetPosition(positionX, positionY);
	if (m_backgroundImage) {
		m_backgroundImage->SetPosition(positionX , positionY);
	}

	if (m_textButton) {
		m_textButton->SetPosition(positionX, positionY);
	}
}

UIText* UIButton::AddUIText(std::string text)
{
	if (m_textButton == nullptr) {
		m_textButton = new UIText(GetWidgetContext());
	}
	return m_textButton;
}

UIText& UIButton::GetUIText() const
{
	return *m_textButton;
}
