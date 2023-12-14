#include "GameWidget.h"

#include "GameState/GameState.h"
#include "UIElements/UI_Image/UIImage.h"
#include "UIElements/UI_Button/UIButton.h"
#include "UIElements/UI_CheckBox/UICheckbox.h"
#include "UIElements/UI_TextField/UITextField.h"

GameWidget::GameWidget(sf::Vector2f size, GameDataRef& gameDataRef) 
	: UIWidget(size, gameDataRef)
{
	GameState* _currentState = reinterpret_cast<GameState*>(_gameDataRef.get()->machine.GetActiveState().get());

	UIImage* backgroundImage = addElement<UIImage>("background image");
	backgroundImage->SetTexture(_gameDataRef.get()->m_assetManager.GetTexture("Game Background"));
	backgroundImage->SetScale(_size.x / backgroundImage->_size.x, _size.y / backgroundImage->_size.y);

	UIButton* launchButton = addElement<UIButton>("launch button");
	launchButton->SetBackgroundImage(_gameDataRef.get()->m_assetManager.GetTexture("Resume Button"));
	launchButton->SetScale(.12f, .12f);
	launchButton->SetPosition(_size.x / 2 - launchButton->_size.x * 2.5f, size.y / 2 + launchButton->_size.y * 3.5f);
	launchButton->BindOnClick(_currentState, &GameState::Start);

	UIButton* pauseButton = addElement<UIButton>("pause button");
	pauseButton->SetBackgroundImage(_gameDataRef.get()->m_assetManager.GetTexture("Pause Button"));
	pauseButton->SetScale(.1f, .1f);
	pauseButton->SetPosition(_size.x - (pauseButton->_size.x * 2), 5.5f);
	pauseButton->BindOnClick(_currentState, &GameState::PauseGame);

	UICheckbox* checkboxDiagMode = addElement<UICheckbox>("checkbox diagonal mode");
	checkboxDiagMode->Init(
		_gameDataRef.get()->m_assetManager.GetTexture("Check Box Unchecked"),
		_gameDataRef.get()->m_assetManager.GetTexture("Check Box Checked"),
		"Diagonal Movement",
		_gameDataRef.get()->m_assetManager.GetFont("Robotto Font")
	);
	checkboxDiagMode->SetPosition(_size.x / 4 - checkboxDiagMode->_size.x, _size.y / 2 - checkboxDiagMode->_size.y);
	checkboxDiagMode->BindOnClick(_currentState, &GameState::DiagonalMode);

	UICheckbox* checkboxDebugMode = addElement<UICheckbox>("checkbox debug mode");
	checkboxDebugMode->Init(
		_gameDataRef.get()->m_assetManager.GetTexture("Check Box Unchecked"),
		_gameDataRef.get()->m_assetManager.GetTexture("Check Box Checked"),
		"Debug Mode",
		_gameDataRef.get()->m_assetManager.GetFont("Robotto Font")
	);
	checkboxDebugMode->SetPosition(checkboxDiagMode->_position.x + (checkboxDiagMode->_size.x - checkboxDebugMode ->_size.x), checkboxDiagMode->_position.y + 50.f);
	checkboxDebugMode->BindOnClick(_currentState, &GameState::DebugMode);

	UIButton* forwardDebugButton = addElement<UIButton>("forward button");
	forwardDebugButton->SetBackgroundImage(_gameDataRef.get()->m_assetManager.GetTexture("Forward Arrow"));
	forwardDebugButton->SetScale(.5f, .5f);
	forwardDebugButton->SetPosition(_size.x / 2 + forwardDebugButton->_size.x * 2 + 1.f,  size.y / 2 + (forwardDebugButton->_size.y * 3.33f));
	forwardDebugButton->BindOnClick(_currentState, &GameState::ForwardDebug);

	UIButton* backwardDebugButton = addElement<UIButton>("backword button");
	backwardDebugButton->SetBackgroundImage(_gameDataRef.get()->m_assetManager.GetTexture("Backward Arrow"));
	backwardDebugButton->SetScale(.5f, .5f);
	backwardDebugButton->SetPosition(_size.x / 2 + backwardDebugButton->_size.x - 1.f, size.y / 2 + (backwardDebugButton->_size.y * 3.33f));
	backwardDebugButton->BindOnClick(_currentState, &GameState::BackwardDebug);

	UIButton* clearAllButton = addElement<UIButton>("clear button");
	clearAllButton->SetBackgroundImage(_gameDataRef.get()->m_assetManager.GetTexture("Clear Button"));
	clearAllButton->SetScale(.15f, .15f);
	clearAllButton->SetPosition(_size.x / 2 - clearAllButton->_size.x / 2, clearAllButton->_size.y * 2);
	clearAllButton->BindOnClick(_currentState, &GameState::ClearAll);

	UIButton* clearPathButton = addElement<UIButton>("clear path button");
	clearPathButton->SetBackgroundImage(_gameDataRef.get()->m_assetManager.GetTexture("Clear Path Button"));
	clearPathButton->SetScale(.15f, .15f);
	clearPathButton->SetPosition(_size.x / 2 + clearAllButton->_size.x + clearPathButton->_size.x / 2, clearPathButton->_size.y * 2);
	clearPathButton->BindOnClick(_currentState, &GameState::ClearPath);

	/*
	UITextField* inputXGrid = addElement<UITextField>("input x grid");
	inputXGrid->SetScale(0.05f, 0.05f);
	inputXGrid->SetPosition(5.f, 50.f);
	inputXGrid->SetFont(_gameDataRef.get()->m_assetManager.GetFont("Robotto Font"));
	inputXGrid->SetMaxChar(2);
	inputXGrid->SetSizeChar(400);
	inputXGrid->SetNumericsOnly(true);
	*/
}

GameWidget::GameWidget(UIElement* parent, sf::Vector2f size, std::string& name) 
	: UIWidget(parent, size, name)
{
}

GameWidget::~GameWidget()
{
}
