#pragma once
#include"Enemy.h"
#define WHITE_BBOX_WIDTH 32
#define WHITE_BBOX_HEIGHT 62

#define WHITE_GRAVITY			0.001f
#define WHITE_WALKING_SPEED			0.10f

#define TIME_SPAWN_WEAPON 1500
#define TIME_WAIT		450
#define NEARLY_WEAPON	10
#define TIME_WAIT_BONE	  3000

#define DISTANCE_FAR_SIMON			96
#define DISTANCE_WALKING_FAR_SIMON	64


enum class WHITESTATE {
	WALKING,
	JUPM,
	JUPMBACK
};

class White :public Enemy
{
private:
	int left = false;
	int _endPos;
	int _startPos;
	bool isSpawnWeapon = false;
	bool isJumpRight = true;
	int numWeapon = 0;
	DWORD timeSpawn = 0;
	DWORD loadTimeSpawn = 0;
	WHITESTATE state;
	bool isJump = true;
	bool isWalking = true;
	int randBone = 0;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	void SetState(WHITESTATE state);

	White();
};



