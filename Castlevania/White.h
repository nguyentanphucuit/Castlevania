#pragma once
#include"Enemy.h"
#define WHITE_BBOX_WIDTH 32
#define WHITE_BBOX_HEIGHT 62

#define WHITE_GRAVITY			0.002f
#define WHITE_WALKING_SPEED			0.10f

#define TIME_SPAWN_WEAPON 1500
class White :public Enemy
{
private:
	int left = false;
	int _endPos;
	int _startPos;
	bool isSpawnWeapon = false;
	int numWeapon = 0;
	int numWeapon2 = 0;
	DWORD timeSpawn = 0;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	void Area(int startPos, int endPos);
	void SetisSpawnWeapon();
	White();
};



