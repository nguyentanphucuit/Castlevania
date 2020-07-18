#pragma once
#include "Enemy.h"
#define ZOMBIE_BBOX_WIDTH 32
#define ZOMBIE_BBOX_HEIGHT 64

#define ZOMBIE_GRAVITY			0.002f
#define ZOMBIE_WALKING_SPEED			0.10f

#define TIME_SPAWN_ZOMBIE		500

class Zombie :public Enemy
{
private:
	int left = false;
	int _endPos;
	int _startPos;
	int nxZ;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	void Nx(int nx);

	Zombie();
};



