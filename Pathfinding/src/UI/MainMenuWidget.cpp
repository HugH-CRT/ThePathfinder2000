#include "MainMenuWidget.h"
#include "UIElements/UIButton.h"
#include "UIElements/UIElement.h"
#include "UIElements/UIImage.h"


MainMenuWidget::MainMenuWidget(const int width, const int height, const GameDataRef& dataRef) : UIWidget(width, height, dataRef)
{
	UIElement* background = addElement<UIImage>("Background");
	background->SetTexture(GetGameDataRef()->m_assetManager.GetTexture("Main Menu Background"), true);
	background->SetScale(GetWidth() / background->GetWidth(), GetHeight() / background->GetHeight());

	UIElement* playButton = addElement<UIButton>("Play Button");
	playButton->SetTexture(GetGameDataRef()->m_assetManager.GetTexture("Play Button"), true);
	playButton->SetPosition(GetWidth() / 2 - playButton->GetWidth() / 2, GetHeight() / 2 - playButton->GetHeight() / 2);

	UIElement* gameTitle = addElement<UIImage>("Game Title");
	gameTitle->SetTexture(GetGameDataRef()->m_assetManager.GetTexture("Game Title"), true);
	gameTitle->SetScale(0.2f, 0.2f);
	gameTitle->SetPosition(GetWidth() / 2 - gameTitle->GetWidth() / 2, gameTitle->GetHeight() * 0.1f);
	
}

MainMenuWidget::~MainMenuWidget()
{
}

void MainMenuWidget::draw(sf::RenderWindow& window)
{
	UIWidget::draw(window);
}
