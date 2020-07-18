#pragma once
#include"GameObject.h"

#define WHIP_ANI_NORMAL 0 
#define WHIP_ANI_CHAIN 1 
#define WHIP_ANI_MORNINGSTAR 2 


#define WHIP_BBOX_NORMAL_HEIGHT 50
#define WHIP_BBOX_NORMAL_WIDTH 40

#define NEARLY_WIDTH_01		20
#define NEARLY_WIDTH_02		30

#define DISTANCE_EFFECT 10
#define DISTANCE_EFFECT_Y 20


enum WHIPSTATE
{
	NORMAL,
	CHAIN,
	MORINGSTAR
};

class Whip:public CGameObject
{
private:
	WHIPSTATE state;
	UINT  damage = 1;
public:
	bool ColOneTime=false;
	Whip()
	{

		this->state = WHIPSTATE::NORMAL;

		AddAnimation("WHIP_ANI_NORMAL", false);
		AddAnimation("WHIP_ANI_CHAIN",false);
		AddAnimation("WHIP_ANI_MORNINGSTAR",false);
	}
	void ResetAttack() {
		this->animations[WHIP_ANI_NORMAL]->ResetFrame();
		this->animations[WHIP_ANI_CHAIN]->ResetFrame();
		this->animations[WHIP_ANI_MORNINGSTAR]->ResetFrame();
	}
	virtual void Render();

	void Upgrade();
	void SetNxDirection(DIRECTION nx) { this->nx = nx; }
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	WHIPSTATE GetState() { return this->state; };
	void SetState(WHIPSTATE state);
	void ResetState() { this->state = WHIPSTATE::NORMAL; };
};

