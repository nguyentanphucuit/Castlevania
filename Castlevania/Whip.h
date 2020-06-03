#pragma once
#include"GameObject.h"

#define WHIP_ANI_NORMAL 0 
#define WHIP_ANI_CHAIN 1 
#define WHIP_ANI_MORNINGSTAR 2 


#define WHIP_BBOX_NORMAL_HEIGHT 50
#define WHIP_BBOX_NORMAL_WIDTH 40


enum WHIPSTATE
{
	NORMAL,
	CHAIN,
	MORINGSTAR
};

class Whip:public CGameObject
{
private:
	int currentAnimation = 0;
	WHIPSTATE state;
public:
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
	void ResetAnimationFrame() {
		animations[currentAnimation]->ResetAnimation();
	}
	void ResetLastFrame() {
		animations[currentAnimation]->ResetLastFrame();
	}
	void SetVelocity(float vx, float vy) {
		this->vx = vx;
		this->vy = vy;

	};
	bool CheckLastFrame();
};

