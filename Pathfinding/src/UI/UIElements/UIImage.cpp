#include "UIImage.h"

UIImage::UIImage(UIWidget& uiContext) : UIElement(uiContext)
{
}

UIImage::UIImage(UIWidget& uiContext, std::string name) : UIElement(uiContext, name)
{
}

UIImage::~UIImage()
{
}

void UIImage::Draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
