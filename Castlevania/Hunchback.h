#pragma once
#include"Enemy.h"
#define HUNCHBACK_BBOX_WIDTH 32
#define HUNCHBACK_BBOX_HEIGHT 32

#define HUNCHBACK_GRAVITY			0.002f
#define HUNCHBACK_WALKING_SPEED			0.10f

#define HUNCHBACK_ANI_READY 0
#define HUNCHBACK_ANI_JUMP 1

#define ACTIVE_HUNCHBACK_X 250

#define TIME_ACTIVE 750
enum class HUNCHBACK {
	READY,
	JUMP
};

class Hunchback :public Enemy
{
private:
	int left = false;
	int _endPos;
	int _startPos;
	int _num;
	HUNCHBACK state;
	bool jump = false;
	DWORD waitTimeActive;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void OnTouchingGround();
	void Num(int num);
	void SetState(HUNCHBACK state);
	Hunchback();
};



