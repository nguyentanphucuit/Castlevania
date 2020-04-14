#pragma once
#include"GameObject.h"

#define WHIP_ANI_NORMAL 0 //3 frame
#define WHIP_ANI_CHAIN 1 // 3 frame
#define WHIP_ANI_MORNINGSTAR 2 // cái này tới 12 frame 


#define WHIP_BBOX_NORMAL_HEIGHT 50
#define WHIP_BBOX_NORMAL_WIDTH 50


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
public:
	Whip()
	{

		this->state = WHIPSTATE::NORMAL;
		//thêm ani
		AddAnimation("WHIP_ANI_NORMAL");
		AddAnimation("WHIP_ANI_CHAIN");
		AddAnimation("WHIP_ANI_MORNINGSTAR");
	}
	void ResetAttack() {
		this->animations[WHIP_ANI_NORMAL]->ResetFrame();
		this->animations[WHIP_ANI_CHAIN]->ResetFrame();
		this->animations[WHIP_ANI_MORNINGSTAR]->ResetFrame();
	}
	virtual void Render();
	void SetNxDirection(int nx) { this->nx = nx; }
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	WHIPSTATE GetState() { return this->state; };
	void SetState(WHIPSTATE state);

};

