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
	virtual void Start(LevelManager* currentLevel, float speed);
	virtual void Update(float dt) override;
	virtual void Draw() override;

	StelAnimation* GetModel();
private:
	// Transform
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