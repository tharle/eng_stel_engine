#pragma once
#include "StelComponent.h"
#include "StelObserver.h"
#include "AEnemyState.h"
#include "StelAnimation.h"
#include "Chest.h"

class AEnemyState;
class StelAnimation;

class Enemy : public StelComponent, public IUpdatable {
private:
	StelEntity* m_Player = nullptr;
	AEnemyState* m_CurrentState = nullptr;
	std::map<std::string, AEnemyState*> m_States;
	StelAnimation* m_Model = nullptr;
	bool m_IsChestOpen = false;
	bool m_IsAlive = true;

public:
	Enemy(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Enemy() = default;

	virtual void Update(float dt) override;
	virtual void Destroy() override;
	virtual void Start(std::string spriteSheet, StelEntity* player);
	virtual void ChangeState(const std::string& state);

	inline bool IsActive() { return m_IsAlive; }
	inline void SetAlive(bool value) { m_IsAlive = value; }
	inline StelAnimation& GetAnimation() { return *m_Model; }

	StelPointF GetDiffPlayer();


	bool IsCurrentState(AEnemyState* state) {
		return m_CurrentState == state;
	};
};

class EnemyStateIdle : public AEnemyState, public StelObserver<int>
{
public:
	EnemyStateIdle(Enemy* parent) : AEnemyState(parent) {};
	virtual ~EnemyStateIdle() = default;

	virtual void OnEnter() override
	{
		Chest::OnOpenChest.AddListener(this);
		m_Enemy->GetAnimation().Play(ENEMY_STATE_IDLE, false);
	};
	
	virtual void Execute(float dt) 
	{
		StelPointF diff = m_Enemy->GetDiffPlayer();
		StelRectF collider = m_Enemy->GetTransform().GetTrueRect();

		if (diff.x < 0 && abs(diff.x) > collider.w) m_Enemy->GetAnimation().SetFrame(1);
		else if (diff.x <= 0 && abs(diff.x) <= collider.w) m_Enemy->GetAnimation().SetFrame(2);
		else if (diff.x >= 0 && abs(diff.x) <= collider.w) m_Enemy->GetAnimation().SetFrame(3);
		else if (diff.x > 0 && abs(diff.x) > collider.w) m_Enemy->GetAnimation().SetFrame(4);
	};

	virtual void OnExit() 
	{
		//Chest::OnOpenChest.RemoveListener(this);
	};

	virtual void OnNotify(const int& eventId)
	{
		if (eventId == EVENT_OPEN_CHEST_ID)
		{
			m_Enemy->ChangeState(ENEMY_STATE_ATTACK);
		}
	};

	virtual bool IsActive() { return m_Enemy->IsCurrentState(this); }
};


class EnemyStateAttack : public AEnemyState, public StelObserver<int>
{
public:
	EnemyStateAttack(Enemy* parent) : AEnemyState(parent) {};
	virtual ~EnemyStateAttack() = default;

	virtual void OnEnter() override
	{
		Chest::OnGetPearl.AddListener(this);
		m_Enemy->GetAnimation().Play(ENEMY_STATE_ATTACK, true);
	};

	virtual void Execute(float dt)
	{
	};

	virtual void OnExit()
	{
		//Chest::OnGetPearl.RemoveListener(this);
	};

	virtual void OnNotify(const int& eventId)
	{
		if (eventId == EVENT_GET_PEARL_ID)
		{
			m_Enemy->ChangeState(ENEMY_STATE_DEAD);
		}
	};

	virtual bool IsActive() { return m_Enemy->IsCurrentState(this); }
};

class EnemyStateDead: public AEnemyState
{
public:
	EnemyStateDead(Enemy* parent) : AEnemyState(parent) {};
	virtual ~EnemyStateDead() = default;

	virtual void OnEnter() override
	{
		m_Enemy->GetAnimation().Stop();
		m_Enemy->GetAnimation().SetFrame(0);
		m_Enemy->SetAlive(false);
		m_Enemy->Destroy();
	};

	virtual void Execute(float dt)
	{
	};

	virtual void OnExit()
	{
	};
};