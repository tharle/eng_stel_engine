#pragma once
#include "StelComponent.h"

class StelAnimation;
class LevelManager;


// All controls for player
class PlayerControls : public StelComponent, public IDrawable, public IUpdatable
{
public:
	PlayerControls(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~PlayerControls() = default;
	virtual void Start(LevelManager* currentLevel);
	virtual void Update(float dt) override;
	virtual void Draw() override;


	void SetPostion(StelPointF position);
	void SetSpeed(float speed);
	void SetSize(StelPointF size, float scaleFactor);

	StelAnimation* GetModel();
private:
	// Transform
	StelPointF m_Position{0, 0};
	StelPointF m_Size = {0.0f, 0.0f};
	float m_ScaleFactor = 1.0f;
	StelRectF m_Collider = StelRectF::Zero();

	// Player model
	float m_Speed = 0;

	// Animation
	StelAnimation* m_Model = nullptr;
	int m_CurrentFrame = 0;
	int m_MaxFrame = 0;

	// Audio
	size_t m_RemoveSfx = 0;
	size_t m_WalkSfx = 0;
	float m_CooldownWalkSound = 0.0f;

	//Fonts Loadeds
	size_t m_TitleFontId = 0;
	size_t m_DecrpFontId = 0;

	// Level
	LevelManager* m_CurrentLevel = nullptr;


	void Move(float dt);
	void MouseEvents();
	void AudioUpdate();
	
};