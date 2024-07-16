#pragma once
#include "StelComponent.h"

#define COOLDOWN_CHANGE_SCENE 1.0f
#define COOLDOWN_WALK_SOUND 0.2f

class StelAnimation;
class LevelManager;

class PlayerControls : public StelComponent, public IDrawable, public IUpdatable
{
public:
	PlayerControls(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~PlayerControls() = default;
	virtual void Start() override;
	virtual void Update(float dt) override;
	virtual void Draw() override;


	void SetPostion(StelPointF position);
	void SetSpeed(float speed);

	StelAnimation* GetModel();
	LevelManager* GetLevel();
private:
	// Delay for keydown
	float m_CooldownChangeScene = COOLDOWN_CHANGE_SCENE;
	float m_CooldownWalkSound = 0.0f;

	// Physics
	StelPointF m_Position{0, 0};
	float m_Speed = 0;
	StelAnimation* m_Model = nullptr;
	int m_CurrentFrame = 0;
	int m_MaxFrame = 0;

	// Audio
	size_t m_AmbianceMusic = 0;
	size_t m_RemoveSfx = 0;
	size_t m_WalkSfx = 0;

	//Fonts Loadeds
	size_t m_TitleFontId = 0;
	size_t m_DecrpFontId = 0;


	void Move(float dt);
	void MouseEvents();
	void AudioUpdate();
	void ChangeScene(float dt);
	// JAI PAS OUBLIE DE ENLEVER ÇA
	//void NextFrame();
};