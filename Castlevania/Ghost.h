#pragma once
#include"Enemy.h"
#define GHOST_BBOX_WIDTH 32
#define GHOST_BBOX_HEIGHT 32

#define GHOST_GRAVITY			0.002f
#define GHOST_FLY_SPEED			0.10f

#define GHOST_FLY_SPEED_Y		0.02f
#define GHOST_OY_HEIGHT			5
class Ghost :public Enemy
{
private:
	int left = false;
	int _endPos;
	int _startPos;
	float oy;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	void SetOy() {
		this->oy = this->y;
	}

	void Area(int startPos, int endPos);
	Ghost();
};



