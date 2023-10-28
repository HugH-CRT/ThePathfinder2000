/**
* @file StateMachine.h
*
* @brief Manage the states of the game
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"

#include <memory>
#include <stack>

typedef std::unique_ptr<State> StateRef;

/**
* @class StateMachine
* @brief
*/
class StateMachine
{
public: 
	StateMachine();
	StateMachine(const StateMachine&) = delete;
	StateMachine& operator=(const StateMachine&) = delete;
	~StateMachine() { }

	void AddState(StateRef newState, bool isReplacing = true);
	void ProcessStateChanges();
	void RemoveState();

	StateRef& GetActiveState();

private:
	std::stack<StateRef> _states;
	StateRef _newState;

	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;
};

#endif /* STATE_MACHINE_H */