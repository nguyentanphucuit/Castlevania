#pragma once
#include"HiddenObject.h"
#include"EnemyFactory.h"


class Spawner:public HiddenObject
{
private:
	DWORD spawn_start;
	CEnemy enemyDef;
	DWORD respawnTime;
	DWORD delayTime;
	DWORD zombieTime = 0;
	int num;
	int startPos;
	int endPos;
	bool isSpawned = false;
	int nxE;
	int numSpawn;

	DWORD counter_start = 0;
public:
	int numHunchback = 0;
	int numGhost = 0;
	int numBlackKnight = 0;
	int numBat = 0;
	int numRaven = 0;
	int numWhite = 0;
	int numZombie = 0;
	Spawner(CEnemy enemyDef, DWORD respawnTime, int num,int startPos,int endPos, int nx) :HiddenObject()
	{
		this->enemyDef = enemyDef;
		this->respawnTime = respawnTime;
		this->num = num;
		this->startPos = startPos;
		this->endPos = endPos;
		this->nxE = nx;
	}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

