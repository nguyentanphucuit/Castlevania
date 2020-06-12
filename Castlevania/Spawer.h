#pragma once
#include"HiddenObject.h"
#include"EnemyFactory.h"

class Spawner:public HiddenObject
{
private:
	DWORD spawn_start;
	CEnemy enemyDef;
	DWORD respawnTime;
	int num;
	bool isSpawned = false;

public:
	Spawner(CEnemy enemyDef, DWORD respawnTime, int num) :HiddenObject()
	{
		this->enemyDef = enemyDef;
		this->respawnTime = respawnTime;
		this->num = num;
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

