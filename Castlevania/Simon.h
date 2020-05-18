#pragma once
#include "GameObject.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.15f  //0.15
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.0015f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_UPSTAIR_VELOCITY 0.04f  // stair

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400

#define SIMON_ANI_IDLE 0 
#define SIMON_ANI_WALKING 1 
#define SIMON_ANI_SIT 2 
#define SIMON_ANI_STAND_ATTACK 3 
#define SIMON_ANI_SIT_ATTACK 4 
#define SIMON_ANI_UP_WHIP 5
#define SIMON_ANI_STEP_UPSTAIR 6

#define SIMON_ANI_DIE	8

#define	SIMON_LEVEL_SMALL	1
#define	SIMON_LEVEL_BIG		2

#define SIMON_BBOX_WIDTH  32
#define SIMON_BBOX_HEIGHT 62


#define SIMON_SPRITE_WIDTH  60
#define SIMON_SPRITE_HEIGHT 66
//#define SIMON_SMALL_BBOX_WIDTH  13
//#define SIMON_SMALL_BBOX_HEIGHT 15

#define SIMON_UNTOUCHABLE_TIME 5000
#define SIMON_UPGRADE_WHIP_TIME 500

#define SIMON_ATTACK_TIME 350


 enum class SIMONSTATE 
{
	IDLE,
	WALKING_RIGHT,
	WALKING_LEFT,
	SIT,
	JUMP,
	DIE,
	FIGHT_STAND,
	FIGHT_SIT,
	UPWHIP,
	ENTERENTRANCE,
	RETROGRADE,
	STAIR,
};

 enum class EWeapon;

class CSIMON : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD fight_start; // biến đếm thời gian đánh khi bắt đầu đánh sẽ đếm, khi đủ 350ms reset
	DWORD upgrade_start;
	
	SIMONSTATE state;
	Whip* whip;
	EWeapon currentWeapon;
	bool spawnWeapon = false;
	bool isSpawnWeapon = false; 
	bool isStair = false;
public: 
	CSIMON();
	bool isOnGround = false;
	bool isTouchRetroGrade = true;
	bool ResetSpawnWeapon() { return this->isSpawnWeapon = false; };
	bool IsSpawnWeapon() { return spawnWeapon; };
	void SpawnWeapon(bool flag) { this->spawnWeapon = flag; };
	
	EWeapon GetCurrentWeapon() { return this->currentWeapon; };

	DWORD GetFightTime() { return this->fight_start; }
	void ResetFightTime() { this->fight_start = 0; }

	DWORD GetUpgradeTime() { return this->upgrade_start; }
	void ResetUpgradeTime() { this->upgrade_start = 0; }

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(SIMONSTATE state);
	void ResetAttack() {
		whip->ResetAttack();
		animations[SIMON_ANI_STAND_ATTACK]->ResetFrame();
		animations[SIMON_ANI_SIT_ATTACK]->ResetFrame();
		this->fight_start = 0;
	}
	SIMONSTATE GetState() {
		return this->state;
	}
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};