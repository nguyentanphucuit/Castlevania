#pragma once
#include"GameObject.h"
#define ENEMY_SPWAWN_TIME 2000
#include"Game.h"
#include"Debug.h"
class Enemy :public CGameObject
{
protected:

public:
	
	void SetNx(DIRECTION nx) {
		this->nx = nx;
	}
	void UpdateEnemy();
};

