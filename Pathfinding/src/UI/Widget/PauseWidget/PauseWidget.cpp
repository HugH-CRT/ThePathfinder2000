#include "PauseWidget.h"

#include "PauseState/PauseState.h"
#include "UIElements/UI_Image/UIImage.h"
#include "UIElements/UI_Button/UIButton.h"

PauseWidget::PauseWidget(sf::Vector2f size, GameDataRef& gameDataRef) 
	: UIWidget(size, gameDataRef)
{
	PauseState* pauseState = reinterpret_cast<PauseState*>(_gameDataRef.get()->machine.GetActiveState().get());

	UIImage* backgroundImage = addElement<UIImage>("background image");
	backgroundImage->SetTexture(_gameDataRef.get()->m_assetManager.GetTexture("Pause Background"));
	backgroundImage->SetScale(_size.x / backgroundImage->_size.x, _size.y / backgroundImage->_size.y);

	UIButton* resumeButton = addElement<UIButton>("resume button");
	resumeButton->SetBackgroundImage(_gameDataRef.get()->m_assetManager.GetTexture("Resume Button"));
	resumeButton->SetScale(.1f, .1f);
	resumeButton->SetPosition(_size.x / 2 - resumeButton->_size.x / 2, _size.y / 3 - resumeButton->_size.y / 2);
	resumeButton->BindOnClick(pauseState, &PauseState::ResumeState);

	UIButton* homeButton = addElement<UIButton>("home button");
	homeButton->SetBackgroundImage(_gameDataRef.get()->m_assetManager.GetTexture("Home Button"));
	homeButton->SetScale(.1f, .1f);
	homeButton->SetPosition(_size.x / 2 - homeButton->_size.x / 2, _size.y / 3 * 2 - homeButton->_size.y / 2);
	homeButton->BindOnClick(pauseState, &PauseState::BackToHome);
}

PauseWidget::PauseWidget(UIElement* parent, sf::Vector2f size, std::string& name)
	: UIWidget(parent, size, name)
{
}

PauseWidget::~PauseWidget()
{
}
