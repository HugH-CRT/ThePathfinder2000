/**
* @file StateMachine.cpp
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
*/
#include "StateMachine.h"

/**
* @fn StateMachine
* @brief Constructor
*/
StateMachine::StateMachine()
	: _isRemoving(false)
	  , _isAdding(false)
	  , _isReplacing(false)
{
}

/**
* @fn AddState
* @brief Add a new state to the stack
* @param newState : the new state to add
* @param isReplacing : if true, the current state will be replaced by the new one
*/
void StateMachine::AddState(StateRef newState, const bool isReplacing)
{
	_isAdding = true;
	_isReplacing = isReplacing;
	_newState = std::move(newState);
}

/**
* @fn RemoveState
* @brief Remove the current state 
*/
void StateMachine::RemoveState()
{
	_isRemoving = true;	
}

/**
* @fn ProcessStateChanges
* @brief Handle the state changes	   
*/
void StateMachine::ProcessStateChanges()
{
	// Remove the current state
	if (_isRemoving && !_states.empty())
	{
		_states.pop();

		if (!_states.empty())
		{
			_states.top()->Resume();
		}

		_isRemoving = false;
	}

	// Add the new state
	if (_isAdding)
	{
		if (!_states.empty())
		{
			if (_isReplacing)
			{
				_states.pop();
			}
			else
			{
				_states.top()->Pause();
			}
		}

		_states.push(std::move(_newState));
		_states.top()->Init();
		_isAdding = false;
	}
}

/**
* @fn GetActiveState
* @brief Return the current state  
* @return the current state
*/
StateRef& StateMachine::GetActiveState()
{
	return _states.top();
}