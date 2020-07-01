#pragma once
#include"Enemy.h"

#define PHANTOM_BBOX_HEIGHT 45
#define PHANTOM_BBOX_WIDTH 97

#define ACTIVE_PHANTOM_X 100
#define ACTIVE_PHANTOM_Y 150

#define PHANTOM_OY_HEIGHT 100 //độ cao sóng  sin khi bat di chuyen

#define PHANTOM_ANI_IDLE 0
#define PHANTOM_ANI_FLY 1

#define FLY_FAST 0.2f
#define FLY_SLOW 0.1f

#define WAIT_TIME 1500

enum class PHANTOMSTATE {
	IDLE,
	FLY
};

class Phantom :public Enemy
{
private:
	PHANTOMSTATE state;
	
	DWORD waiting_start = 0;
	DWORD fly_ramdom_start = 0;
	DWORD start_attack = 0;

	D3DXVECTOR2 target;
	RECT box_attive;
	RECT box_fast_attack;
	RECT box_slow_attack;

	float maxTime = 0;
	void FlyTo(D3DXVECTOR2 target, float v);
public:
	
	float angle = 1.;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetState(PHANTOMSTATE state);
	Phantom();
};

