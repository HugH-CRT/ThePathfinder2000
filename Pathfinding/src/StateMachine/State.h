#ifndef STATE_H
#define STATE_H

class State
{
public:
	virtual ~State() = default;
	virtual void Init() = 0;

	virtual void HandleInput() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;
	virtual void LoadTextures() = 0;
	virtual void SetTextures() = 0;

	virtual void Pause() {}
	virtual void Resume() {}
};

#endif /* STATE_H */