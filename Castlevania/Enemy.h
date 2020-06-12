#pragma once
#include "GameObject.h"
#define ENEMY_SPWAWN_TIME 2000
#include "Game.h"
#include "Debug.h"
class Enemy :public CGameObject
{
protected:
	unsigned int score;
	int hp;
	DWORD spawn_start;
	bool isFreeze = false;

public:
	void SubtractHP(unsigned int point)
	{

		this->hp = this->hp - point;
		if (this->hp < 0)
		{
			this->hp = 0;
		}

	};
	void SetNx(DIRECTION nx) {
		this->nx = nx;
	}
	void UpdateEnemy();
	void SetFreeze(bool flag) {
		this->isFreeze = flag;
	}

	void ResetSpawnStart() {
		this->spawn_start = GetTickCount();
	}

	unsigned int GetScore()
	{
		return this->score;
	}
	unsigned int GetHp() {
		return this->hp;
	}
	Enemy() :CGameObject() {
		score = hp = 0;
		spawn_start = 0;

	}
	~Enemy();
};

