#include "StateMachine.h"

StateMachine::StateMachine()
{
	_isAdding = false;
	_isRemoving = false;
	_isReplacing = false;
}

/*
 * Brief : Add a new state to the stack
 *
 * @param newState : the new state to add
 * @param isReplacing : if true, the current state will be replaced by the new one
 */
void StateMachine::AddState(StateRef newState, const bool isReplacing)
{
	_isAdding = true;
	_isReplacing = isReplacing;
	_newState = std::move(newState);
}

/*
 * Brief : Remove the current state
 */
void StateMachine::RemoveState()
{
	_isRemoving = true;	
}

/*
 * Brief : Handle the state changes	 
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

/*
 * Brief : Return the current state
 */
StateRef& StateMachine::GetActiveState()
{
	return _states.top();
}