#pragma once
#include "StelComponent.h"
#include "StelEngine.h"

class PlayerControls : public StelComponent, public IDrawable, public IUpdatable
{
public:
	virtual void Update(float dt) override;
	virtual void Draw() override;


	void SetPostion(StelPointF position);
	void SetSpeed(float speed);
private:
	StelPointF m_Position;
	float m_Speed;

	void Move();
	void MouseEvents();
	void AudioUpdate();
};