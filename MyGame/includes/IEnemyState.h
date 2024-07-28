#pragma once

#define ENEMY_STATE_IDLE "IDLE" 
#define ENEMY_STATE_ATTACK "ATTACK"
#define ENEMY_STATE_SLEEP "SLEEP" 
#define ENEMY_STATE_FROZEN "FROZEN"

class Enemy;

class IEnemyState {
public:
	virtual ~IEnemyState() = default;

	virtual void OnEnter(Enemy* enemy) = 0;
	virtual void Execute(Enemy* enemy, float dt) = 0;
	virtual void OnExit(Enemy* enemy) = 0;
};