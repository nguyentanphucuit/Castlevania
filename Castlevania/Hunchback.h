#pragma once
#include"Enemy.h"
#define HUNCHBACK_BBOX_WIDTH 32
#define HUNCHBACK_BBOX_HEIGHT 32

#define HUNCHBACK_GRAVITY			0.002f
#define HUNCHBACK_WALKING_SPEED			0.10f


class Hunchback :public Enemy
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
	Hunchback();
};



