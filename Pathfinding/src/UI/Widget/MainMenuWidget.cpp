#include "MainMenuWidget.h"
#include "UI/UIElements/UIImage.h"
#include "UI/UIElements/UIButton.h"
#include "Game.h"
#include "GameState/GameState.h"

MainMenuWidget::MainMenuWidget(sf::Vector2f size, GameDataRef& gameDataRef) : UIWidget(size, gameDataRef)
{
	UIImage* backgroundImage = addElement<UIImage>("background image");
	backgroundImage->SetTexture(_gameDataRef.get()->m_assetManager.GetTexture("Main Menu Background"));
	backgroundImage->SetScale(_size.x / backgroundImage->_size.x, _size.y / backgroundImage->_size.y);

	UIImage* gameTitleImage = addElement<UIImage>("game title image");
	gameTitleImage->SetTexture(_gameDataRef.get()->m_assetManager.GetTexture("Game Title"));
	gameTitleImage->SetScale(0.2f, 0.2f);
	gameTitleImage->SetPosition((_size.x / 2) - (gameTitleImage->_size.x / 2), 0.2f);

	UIButton* btnPlayGame = addElement<UIButton>("play button");
	btnPlayGame->SetBackgroundImage(_gameDataRef.get()->m_assetManager.GetTexture("Play Button"));
	btnPlayGame->SetPosition(((_size.x / 2) - (btnPlayGame->_size.x / 2)), (size.y / 2 ) - (btnPlayGame->_size.y / 2));
	btnPlayGame->BindOnClick(this, &MainMenuWidget::StartGame);
}

MainMenuWidget::MainMenuWidget(UIElement& parent, sf::Vector2f size, std::string& name) : UIWidget(parent, size, name)
{
}

MainMenuWidget::~MainMenuWidget()
{
}

void MainMenuWidget::StartGame()
{
	_gameDataRef->machine.AddState(std::make_unique<GameState>(_gameDataRef), true);
}