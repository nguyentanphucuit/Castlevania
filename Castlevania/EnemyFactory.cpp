#include "EnemyFactory.h"
#include "PlayScene.h"
#include "Enemy1.h"
#include "Convert.h"


HandleSpawnEnemy* HandleSpawnEnemy::__instance = NULL;



void HandleSpawnEnemy::SpawnEnemy(int enemyDef, int num, DWORD respawntime, float x, float y, DIRECTION nx, float oy)
{
	float cx, cy;
	float px, py;
	CGame::GetInstance()->SetCamPos(cx, cy);
	scene->GetPlayerPosition(px, py);
	if (stopSpawn)
	{
		return;
	}
	switch (enemyDef)
	{
	case BAT: {
		for (size_t i = 0; i < num; i++)
		{
			enemy = new Bat(oy);
			int rank = rand() % 2;
			if (rank == 1)
			{
				enemy->SetPositionInWorld(cx + SCREEN_WIDTH + i * 50 + 34, y);
				enemy->SetNx(DIRECTION::LEFT);
			}
			else
			{
				enemy->SetPositionInWorld(cx - i * 50 - 34, y);
				enemy->SetNx(DIRECTION::RIGHT);

			}
		}
		break;
	}
	}
}

void HandleSpawnEnemy::SpawnFireBall(float x, float y, DIRECTION nx, float vy)
{

}

HandleSpawnEnemy* HandleSpawnEnemy::GetInstance()
{
	if (__instance == NULL) __instance = new HandleSpawnEnemy();
	return __instance;
}
void HandleSpawnEnemy::FreezeEnemy(bool flag)
{

}
void HandleSpawnEnemy::Init(PlayScene* scene)
{
	this->scene = scene;
}
HandleSpawnEnemy::HandleSpawnEnemy()
{

}


HandleSpawnEnemy::~HandleSpawnEnemy()
{
	delete scene;
}
