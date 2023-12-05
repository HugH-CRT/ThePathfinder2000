#include "SplashWidget.h"
#include "UIElements/UI_Image/UIImage.h"

SplashWidget::SplashWidget(const sf::Vector2f& size, GameDataRef& gameDataRef) 
	: UIWidget(size, gameDataRef)
{
	UIImage* backgroundImage = addElement<UIImage>("background image");
	backgroundImage->SetTexture(_gameDataRef.get()->m_assetManager.GetTexture("Splash State Background"));
	backgroundImage->SetScale(_size.x / backgroundImage->_size.x, _size.y / backgroundImage->_size.y);
}

SplashWidget::SplashWidget(UIElement* parent, const sf::Vector2f& size, std::string& name) 
	: UIWidget(parent, size, name)
{
}

SplashWidget::~SplashWidget()
{
}
