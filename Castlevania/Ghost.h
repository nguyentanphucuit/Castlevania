#pragma once
#include"Enemy.h"
#define GHOST_BBOX_WIDTH 32
#define GHOST_BBOX_HEIGHT 32

#define GHOST_GRAVITY			0.002f
#define GHOST_WALKING_SPEED			0.10f


class Ghost :public Enemy
{
private:
	int left = false;
	int _endPos;
	int _startPos;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	void Area(int startPos, int endPos);
	Ghost();
};



