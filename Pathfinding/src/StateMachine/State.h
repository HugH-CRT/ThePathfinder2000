/**
* @file State.h
 *
 * @brief Interface for the states of the game
 *
 * @author yoan.laurain@ynov.com
 *
 */

#ifndef STATE_H
#define STATE_H

class State
{
public:
	virtual ~State() = default;
	
	virtual void Draw(float dt) = 0;
	virtual void HandleInput() = 0;
	virtual void Init() = 0;
	virtual void LoadTextures() = 0;
	virtual void LoadFonts() = 0;
	virtual void SetTexts() = 0;
	virtual void SetScales() = 0;
	virtual void SetPositions() = 0;
	virtual void SetTextures() = 0;
	virtual void Update(float dt) = 0;
	virtual void Pause() {}
	virtual void Resume() {}

};

#endif /* STATE_H */