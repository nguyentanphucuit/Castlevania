#pragma once
#include <d3dx9.h>
#include <utility> 
#include <string>
#include "Enemy.h"

class PlayScene;
class HandleSpawnEnemy
{
	Enemy* enemy;
	bool stopSpawn = false;
	PlayScene* scene;
	static HandleSpawnEnemy* __instance;
public:
	void SpawnEnemy(int enemydef, int num, DWORD respawntime, float x, float y, DIRECTION nx = DIRECTION::RIGHT, float oy = 0);
	void SpawnFireBall(float x, float y, DIRECTION nx, float vy);
	static HandleSpawnEnemy* GetInstance();
	void FreezeEnemy(bool flag);
	void Init(PlayScene* scene);
	HandleSpawnEnemy();
	~HandleSpawnEnemy();
};

