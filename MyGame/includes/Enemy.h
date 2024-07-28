#pragma once
#include "StelComponent.h"
#include "StelObserver.h"

class IEnemyState;
class StelAnimation;

class Enemy : public StelComponent, public IUpdatable, public StelObserver<StelTransform>, public StelObserver<int> {
private:
	IEnemyState* m_CurrentState = nullptr;
	std::map<std::string, IEnemyState*> m_States;
	StelAnimation* m_Model = nullptr;
	bool m_IsChestOpen = false;
	bool m_IsAlive = true;

public:
	Enemy(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Enemy() = default;

	virtual void OnNotify(const StelTransform& playerTransform ) override;
	virtual void OnNotify(const int& isChestOpen ) override;

	//virtual void Start(std::map<std::string, IEnemyState*> states);
	virtual void Start(std::string spriteSheet);
	void ChangeState(const std::string& state);
	void Update(float dt) override;

	inline bool IsActive() { return m_IsAlive; }
};