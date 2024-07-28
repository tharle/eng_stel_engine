#include "Enemy.h"
#include "IEnemyState.h" 
#include "StelAnimation.h"
#include "Chest.h"


void Enemy::Start(std::string spriteSheet)
{
	StelComponent::Start();

	//m_States = states;

	StelPointI size = StelPointI::FromFloat(GetTransform().Size.x, GetTransform().Size.y);
	
	// Animation
	m_Model = m_EntityParent->AddComponent<StelAnimation>();
	m_Model->Init(spriteSheet);
	m_Model->Start();
	m_Model->AddAnimationFrames(1, { 0, 8 }, { size.x, size.y });
	m_Model->AddAnimationFrames(4, { 0, 6 }, { size.x, size .y});

	m_Model->AddClip(ENEMY_STATE_IDLE, 1, 1, 0.0f);
	m_Model->AddClip(ENEMY_STATE_ATTACK, 1, 4, 0.2f);

	m_Model->Play(ENEMY_STATE_IDLE, false);

}

void Enemy::ChangeState(const std::string& state)
{
	if (m_States.count(state) <= 0) return;

	if (m_CurrentState) m_CurrentState->OnExit(this);

	m_CurrentState = m_States[state];
	m_CurrentState->OnEnter(this);
}

void Enemy::Update(float dt)
{
	//if(m_CurrentState != nullptr) m_CurrentState->Execute(this, dt);

	// Looking to Player
	
}


void Enemy::OnNotify(const StelTransform& playerTransform)
{
	if (!m_IsAlive) return;
	if (m_IsChestOpen) return;

	StelPointF playerPos =  playerTransform.Position;
	StelPointF diff = playerPos.Diff(GetTransform().Position);

	if (diff.x < 0 && abs(diff.x) > GetTransform().GetTrueRect().w) m_Model->SetFrame(1);
	else if (diff.x <= 0 && abs(diff.x) <= GetTransform().GetTrueRect().w) m_Model->SetFrame(2);
	else if (diff.x >= 0 && abs(diff.x) <= GetTransform().GetTrueRect().w) m_Model->SetFrame(3);
	else if (diff.x > 0 && abs(diff.x) > GetTransform().GetTrueRect().w) m_Model->SetFrame(4);
}

void Enemy::OnNotify(const int& idEvent)
{
	if (idEvent == EVENT_OPEN_CHEST_ID) 
	{
		m_IsChestOpen = true;
		m_Model->Play(ENEMY_STATE_ATTACK, true);
	}
	else if (idEvent == EVENT_GET_PEARL_ID) 
	{
		m_Model->Stop();
		m_Model->SetFrame(0);
		m_IsAlive = false;
	}
}
