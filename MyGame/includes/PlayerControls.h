#pragma once
#include "StelComponent.h"
#include "StelObserver.h"

#define LAYER_NAME_PLAYER "PLAYER"

#define ANIMATION_PLAYER_DOWN "walk_down"
#define ANIMATION_PLAYER_LEFT "walk_left"
#define ANIMATION_PLAYER_UP "walk_up"
#define ANIMATION_PLAYER_RIGHT "walk_right"

class StelAnimation;
class LevelManager;


// All controls for player
class PlayerControls : public StelComponent, public IUpdatable
{
public:
	PlayerControls(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~PlayerControls();
	virtual void Start(LevelManager* currentLevel, float speed);
	virtual void Update(float dt) override;
	
	inline float GetSpeed() { return m_Speed; }
private:
	// Physics
	StelRectF m_Collider = StelRectF::Zero(); // only for Tilemaps
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