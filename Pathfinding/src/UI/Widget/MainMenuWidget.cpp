#include "MainMenuWidget.h"
#include "UI/UIElements/UIImage.h"
#include "Game.h"

MainMenuWidget::MainMenuWidget(sf::Vector2f size, GameDataRef& gameDataRef) : UIWidget(size, gameDataRef)
{
	UIImage* backgroundImage = addElement<UIImage>("background image");
	backgroundImage->SetTexture(_gameDataRef.get()->m_assetManager.GetTexture("Main Menu Background"));
	backgroundImage->SetScale(_size.x / backgroundImage->_size.x, _size.y / backgroundImage->_size.y);

	UIImage* gameTitleImage = addElement<UIImage>("game title image");
	gameTitleImage->SetTexture(_gameDataRef.get()->m_assetManager.GetTexture("Game Title"));
	gameTitleImage->SetScale(0.2f, 0.2f);
	gameTitleImage->SetPosition((_size.x / 2) - (gameTitleImage->_size.x / 2), 0.2f);
}

MainMenuWidget::MainMenuWidget(UIElement& parent, sf::Vector2f size, std::string& name) : UIWidget(parent, size, name)
{
}

MainMenuWidget::~MainMenuWidget()
{
}
