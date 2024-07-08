#pragma once
#include "StelComponent.h"
#include "StelEngine.h"

class StelSprite;

class PlayerControls : public StelComponent, public IDrawable, public IUpdatable
{
public:
	PlayerControls(StelEntity* parent) : StelComponent(parent) {  }
	~PlayerControls() = default;
	virtual void Start() override;
	virtual void Update(float dt) override;
	virtual void Draw() override;


	void SetPostion(StelPointF position);
	void SetSpeed(float speed);
	StelSprite* GetModel();
private:
	// Delay for keydown
	float m_ElapseTimeTouched = 1.0f;

	// Physics
	StelPointF m_Position{0, 0};
	float m_Speed = 0;
	StelSprite* m_Model = nullptr;

	// Audio
	size_t m_AmbianceMusic = 0;
	size_t m_RemoveSfx = 0;

	//Fonts Loadeds
	size_t m_TitleFontId = 0;
	size_t m_DecrpFontId = 0;

	void Move();
	void MouseEvents();
	void AudioUpdate();
};