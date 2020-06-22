#pragma once
#include "Weapon.h"
#include "Enemy.h"
#define STOPWATCH_FREEZE_TIME 3000


class WStopWatch :public Weapon
{
	Enemy* enemy;
	DWORD motionless;
public:
	virtual void Render() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void  GetBoundingBox(float& l, float& t, float& r, float& b) {
	};
	DWORD CheckFreezeTime() {
		return this->motionless;
	}

	WStopWatch();
};

