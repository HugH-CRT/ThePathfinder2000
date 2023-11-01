#include "MainMenuWidget.h"
#include "UI/UIElements/UIImage.h"
#include "Game.h"

MainMenuWidget::MainMenuWidget(sf::Vector2f size, GameDataRef& gameDataRef) : UIWidget(size, gameDataRef)
{
	UIImage* backgroundImage = addElement<UIImage>("background image");
	backgroundImage->SetTexture(_gameDataRef.get()->m_assetManager.GetTexture("Main Menu Background"));
}

MainMenuWidget::MainMenuWidget(UIElement& parent, sf::Vector2f size, std::string& name) : UIWidget(parent, size, name)
{
}

MainMenuWidget::~MainMenuWidget()
{
}
