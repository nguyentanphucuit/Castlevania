#pragma once
#include"GameObject.h"
#define ENEMY_SPWAWN_TIME 2000
#include "Game.h"
#include "Debug.h"
class Enemy :public CGameObject
{
protected:
	int hp = 0;
public:
	bool IsDestroyed() { return isDestroy; }
	void SetNx(DIRECTION nx) {
		this->nx = nx;
	}
	void UpdateEnemy();
	int GetHp() {
		return this->hp;
	}
	void SubtractHP(unsigned int dame)
	{

		this->hp = this->hp - dame;
		if (this->hp < 0)
		{
			this->hp = 0;
		}

	};
};

