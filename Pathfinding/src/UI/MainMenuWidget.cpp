#include "MainMenuWidget.h"
#include "UIElements/UIButton.h"
#include "UIElements/UIElement.h"


MainMenuWidget::MainMenuWidget(const int width, const int height, const GameDataRef& dataRef) : UIWidget(width, height, dataRef)
{
	UIElement* playButton = addElement<UIButton>("Play Button");
	playButton->m_sprite.setTexture(GetGameDataRef()->m_assetManager.GetTexture("Play Button"));
	playButton->m_sprite.setPosition(SCREEN_WIDTH / 2 - playButton->m_sprite.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - playButton->m_sprite.getGlobalBounds().height / 2);
}

MainMenuWidget::~MainMenuWidget()
{
}

void MainMenuWidget::draw(sf::RenderWindow& window)
{
	UIWidget::draw(window);
}
