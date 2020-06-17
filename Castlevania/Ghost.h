#pragma once
#include"Enemy.h"
#define GHOST_BBOX_WIDTH 32
#define GHOST_BBOX_HEIGHT 32


#define ghost_fly_velocity 0.1f
#define PI 3.14159265359
class Ghost :public Enemy
{
private:
	float minTime = 0;
	D3DXVECTOR2 targer;
public:
	int angle = 45;
	DWORD start_attack = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	Ghost();
};



