#pragma once
#include"Weapon.h"

#define FIREBOMB_GRAVITY 0.001f
#define FIREBOMB_SPEED_VX 0.15f
#define FIREBOMB_SPEED_VY 0.15f

#define FIREBOMB_BBOX_WIDTH 30
#define FIREBOMB_BBOX_HEIGHT 28

#define FIREBOMB_ANI_NORMAL 0
#define FIREBOMB_ANI_BURN	1

#define TIME_FIREBOMB 5000

enum class FIREBOMBSTATE {
	NORMAL,
	BURN
};

class WFireBomb :public Weapon
{
private:
	FIREBOMBSTATE state;
	DWORD time_exist = 0;
	WFireBomb* wFirebomb;
public:
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(FIREBOMBSTATE state);
	FIREBOMBSTATE GetState() { return this->state; }
	WFireBomb();
};

