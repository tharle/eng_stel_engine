#pragma once
#include "StelComponent.h"
#include "StelObserver.h"

#define LAYER_NAME_PLAYER "PLAYER"

#define ANIMATION_PLAYER_DOWN "walk_down"
#define ANIMATION_PLAYER_LEFT "walk_left"
#define ANIMATION_PLAYER_UP "walk_up"
#define ANIMATION_PLAYER_RIGHT "walk_right"

#define PLAYER_SPEED 5.0f

class StelAnimation;
class LevelManager;


// All controls for player
class Player : public StelComponent, public IUpdatable
{
public:
	Player(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Player();
	virtual void Start(LevelManager* currentLevel);
	virtual void Update(float dt) override;
	
	inline float GetSpeed() { return m_Speed; }

	void Die();
private:
	// Physics
	StelRectF m_Collider = StelRectF::Zero(); // only for Tilemaps
	float m_Speed = PLAYER_SPEED;

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
	void InputEvents();
	void AudioUpdate();
};