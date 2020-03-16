#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400

#define SIMON_ANI_IDLE 0 // cai dau tien them vao vector 
#define SIMON_ANI_WALKING 1 // cai dau tien them vao vector 
#define SIMON_ANI_SIT 2 // cai dau tien them vao vector 
#define SIMON_ANI_DIE				8

#define	SIMON_LEVEL_SMALL	1
#define	SIMON_LEVEL_BIG		2

#define SIMON_BIG_BBOX_WIDTH  60
#define SIMON_BIG_BBOX_HEIGHT 66

#define SIMON_SMALL_BBOX_WIDTH  13
#define SIMON_SMALL_BBOX_HEIGHT 15

#define SIMON_UNTOUCHABLE_TIME 5000



// h nhiêu đây trc đã
 enum class SIMONSTATE 
{
	IDLE,
	WALKING_RIGHT,// cần right left vì khi nhấn phím trái phải ta cần biến simon đi hướng nào để vẽ ani phù hợp
	WALKING_LEFT,
	SIT,
	JUMP,
	DIE
};



class CSIMON : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	SIMONSTATE state;
public: 
	CSIMON() : CGameObject()
	{
		level = SIMON_LEVEL_BIG;
		untouchable = 0;
		state = SIMONSTATE::IDLE; // trạng thái ban đầu cần khai báo khi tạo object
		AddAnimation("SIMON_ANI_IDLE");	//0	
		AddAnimation("SIMON_ANI_WALKING");//	1	
		AddAnimation("SIMON_ANI_SIT");//	2	
	


		
	}
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(SIMONSTATE state);
	SIMONSTATE GetState() {
		return this->state;
	}
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};