#pragma once
#include"GameObject.h"
#define ENEMY_SPWAWN_TIME 2000
#include "Game.h"
#include "Debug.h"
class Spawner;
class Enemy :public CGameObject
{
protected:
	unsigned int score;
	int hp = 0;
	bool isMotionless;
	bool isCross;
public:
	Spawner* spawnOwner=NULL;
	bool IsDestroyed() { return isDestroy; }
	void SetNx(DIRECTION nx) {
		this->nx = nx;
	}
	void UpdateEnemy();
	int GetHp() {
		return this->hp;
	}
	void SetMotionless(bool flag) {
		this->isMotionless = flag;
	}
	void SubtractHP(unsigned int dame)
	{

		this->hp = this->hp - dame;
		if (this->hp < 0)
		{
			this->hp = 0;
		}

	};
	unsigned int GetScore()
	{
		return this->score;
	}
};

