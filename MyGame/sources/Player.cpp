#include "Player.h"
#include "StelAnimation.h"
#include "LevelManager.h"
#include "Chest.h"
#include "Projectil.h"


Player::~Player()
{
	Physic().Remove(m_EntityParent);
}

void Player::Start(LevelManager* currentLevel)
{
	StelComponent::Start();

	// Animation
	m_Model = m_EntityParent->AddComponent<StelAnimation>();
	m_Model->Init("Assets/adv_lolo_char.png");
	m_Model->Start();
	m_Model->AddAnimationFrames(5, { 0, 0 }, { 16, 16 });
	m_Model->AddAnimationFrames(5, { 0, 1 }, { 16, 16 });
	m_Model->AddAnimationFrames(5, { 0, 2 }, { 16, 16 });
	m_Model->AddAnimationFrames(5, { 0, 3 }, { 16, 16 });


	m_CurrentLevel = currentLevel;

	// Load sounds and audios
	m_RemoveSfx = Audio().LoadSound("Assets/Audios/Remove1.wav");
	if (m_RemoveSfx == 0)   Log().Print(LOG_WARNING, "ERROR LOAD AUDIO");
	m_WalkSfx = Audio().LoadSound("Assets/Audios/sound_walk.wav");
	if (m_WalkSfx == 0)   Log().Print(LOG_WARNING, "ERROR LOAD AUDIO");

	// Load Fonts
	m_TitleFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 30);
	m_DecrpFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 12);
	m_Model->AddClip(ANIMATION_PLAYER_DOWN, 0, 5, 0.02f);
	m_Model->AddClip(ANIMATION_PLAYER_LEFT, 5, 5, 0.02f);
	m_Model->AddClip(ANIMATION_PLAYER_UP, 10, 5, 0.02f);
	m_Model->AddClip(ANIMATION_PLAYER_RIGHT, 15, 5, 0.02f);

	// COLLIDER
	float offset = 4.0f;
	m_Collider = { -offset,-offset, - offset , - offset };
	Physic().AddToLayer(LAYER_NAME_PLAYER, m_EntityParent);
}


void Player::Update(float dt) 
{
	Move(dt);
	InputEvents();
	AudioUpdate();
}

void Player::Die()
{
}

void Player::Move(float dt)
{
	// In the original game, if you press up/down, will ignore left or right
	float axiosV = Input().GetAxiosVertical();
	float axiosH = axiosV == 0? Input().GetAxiosHorizontal() : 0; 

	if (axiosH == 0 && axiosV == 0)
	{
		m_Model->Stop();
		return;
	}


	StelTransform transform = GetTransform();
	StelPointF position = transform.Position;
	position.x += axiosH * dt * m_Speed * GetTransform().GetTrueRect().h;
	position.y += axiosV * dt * m_Speed * GetTransform().GetTrueRect().h;

	StelRectF collider = {
		position.x - m_Collider.x,
		position.y - m_Collider.y,
		GetTransform().Size.x + m_Collider.x,
		GetTransform().Size.y + m_Collider.y
	};

	// Colling with tile
	if (!m_CurrentLevel->IsColliding(collider.Resize(GetTransform().Scale)))
	{
		transform.Position = position;
		SetTransform(transform);
	}
	

	// Animation	
	if (m_CooldownWalkSound <= 0)
	{
		m_CooldownWalkSound = COOLDOWN_WALK_SOUND;
		Audio().PlaySFX(m_WalkSfx);
	}
	else m_CooldownWalkSound -= dt;
		
	if (axiosV > 0) m_Model->Play(ANIMATION_PLAYER_DOWN, true);
	else if (axiosV < 0) m_Model->Play(ANIMATION_PLAYER_UP, true);
	else if (axiosH < 0) m_Model->Play(ANIMATION_PLAYER_LEFT, true);
	else if (axiosH > 0 ) m_Model->Play(ANIMATION_PLAYER_RIGHT, true);
	
}

void Player::InputEvents()
{
	IEvents::StelEvent stelEvent;
	if(Events().Contanis(IEvents::Quit, stelEvent))
	{
		World().ExitGame();
	}

	if (Input().IsKeyDown(IInput::J)) 
	{
		StelRectF collider = GetTransform().GetTrueRect();
		StelEntity* projectilEntity = World().CreateLater("Projectil");
		projectilEntity->SetTransform({ 6.0f * collider.w, 9.0f * collider.h }, 
			GetTransform().Size, 
			GetTransform().Scale, 
			GetTransform().Angle);
		Projectil* projectil = projectilEntity->AddComponent<Projectil>();
	
		projectil->Start({ 1, 0 });
	}
}

void Player::AudioUpdate()
{
	if (Input().IsKeyDown(IInput::StelKey::Z))
	{
		Audio().PlaySFX(m_RemoveSfx);
	}
}

