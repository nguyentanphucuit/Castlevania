#pragma once
#include "GameObject.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.15f  //0.15
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.0015f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_DEFLECT_SPEED_X 0.2f
#define SIMON_DEFLECT_SPEED_Y 0.35f

#define SIMON_UPSTAIR_VELOCITY 0.04f  // stair
#define SIMON_FALLDOWN_VY 0.8f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400

//STAIR
#define SIMON_ONSTAIR_DISTANCE_X 16
#define SIMON_ONSTAIR_DISTANCE_Y 16
#define SIMON_STATE_UPSTAIR_IDLE 1000
#define SIMON_STATE_UPSTAIR_RIGHT 1100
#define SIMON_STATE_UPSTAIR_LEFT 1200
#define SIMON_STATE_DOWNSTAIR_IDLE 1300
#define SIMON_STATE_DOWNSTAIR_RIGHT 1400
#define SIMON_STATE_DOWNSTAIR_LEFT 1500
#define SIMON_STATE_UPSTAIR_ATTACK 1600
#define SIMON_STATE_DOWNSTAIR_ATTACK 1700
#define SIMON_STATE_FALL_DOWN 1800
#define SIMON_STATE_DEFLECT 1900



#define SIMON_ANI_IDLE 0 
#define SIMON_ANI_WALKING 1 
#define SIMON_ANI_SIT 2 
#define SIMON_ANI_STAND_ATTACK 3 
#define SIMON_ANI_SIT_ATTACK 4 
#define SIMON_ANI_UP_WHIP              5
#define SIMON_ANI_STEP_UPSTAIR            6
#define SIMON_ANI_IDLE_UPSTAIR          7
#define SIMON_ANI_IDLE_DOWNSTAIR         8
#define SIMON_ANI_STEP_DOWNSTAIR            9
#define SIMON_ANI_UPSTAIR_ATTACK            10
#define SIMON_ANI_DOWNSTAIR_ATTACK         11
#define SIMON_ANI_DEFLECT					12
#define SIMON_ANI_DIE						13


#define	SIMON_LEVEL_SMALL	1
#define	SIMON_LEVEL_BIG		2

#define SIMON_BBOX_WIDTH  60
#define SIMON_BBOX_HEIGHT 64


#define SIMON_SPRITE_WIDTH  60
#define SIMON_SPRITE_HEIGHT 66


#define SIMON_UNTOUCHABLE_TIME 3000
#define SIMON_UPGRADE_WHIP_TIME 500

#define SIMON_ATTACK_TIME 350
#define SIMON_UPSTAIR_RIGHT_OFFSET  10
#define SIMON_UPSTAIR_LEFT_OFFSET 16 
#define SIMON_DOWNSTAIR_LEFT_OFFSET 12
#define SIMON_DOWNSTAIR_RIGHT_OFFET 18

#define STEP_STAIR		5

#define SIMON_HP	2
#define SIMON_ENERY 1000

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
	UP_STAIR_RIGHT,
	UP_STAIR_IDLE,
	DOWN_STAIR_RIGHT,
	DOWN_STAIR_IDLE,
	UP_STAIR_LEFT,
	DOWN_STAIR_LEFT,
	UP_STAIR_FIGHT,
	DOWN_STAIR_FIGHT,
	DEFLECT,
};

 enum class EWeapon;

 class CSIMON : public CGameObject
 {

	 int hp;
	 int energy;

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
	 //Stair
	 bool isAutoWalk = false;


	 bool startOnStair = false;
	 bool isColliceWithStair = false;
	 bool isFirstStepOnStair = false;
	 bool isOnStair = false;
	 STAIRDIRECTION onStairDirection = STAIRDIRECTION::DEFAULT;
	 D3DXVECTOR2 stairPos;

	 void HandleFirstStepOnStair();
	 void HandlePerStepOnStair();
 public:
	 CSIMON();

	D3DXVECTOR2 LastStepOnStairPos;
	bool isOnGround = false;
	bool isOnPlatform = false;
	bool isTouchRetroGrade = true;
	bool ResetSpawnWeapon() { return this->isSpawnWeapon = false; };
	bool IsSpawnWeapon() { return spawnWeapon; };
	void SpawnWeapon(bool flag) { this->spawnWeapon = flag; };
	void SetStepOnStairDirection(STAIRDIRECTION dir) {
		this->onStairDirection = dir;
	}
	STAIRDIRECTION CheckStepOnStairDirection() {
		return this->onStairDirection;
	}
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
		animations[SIMON_ANI_UPSTAIR_ATTACK]->ResetFrame();
		animations[SIMON_ANI_DOWNSTAIR_ATTACK]->ResetFrame();
		this->fight_start = 0;
	}
	SIMONSTATE GetState() {
		return this->state;
	}
	bool CheckCanStepUp() {
		if (this->onStairDirection == STAIRDIRECTION::UPLEFT || this->onStairDirection == STAIRDIRECTION::UPRIGHT)
			return true;
		return false;
	}
	bool CheckCanStepDown() {
		if (this->onStairDirection == STAIRDIRECTION::DOWNLEFT || this->onStairDirection == STAIRDIRECTION::DOWNRIGHT)
			return true;
		return false;
	}
	bool CheckStairOnStair() {
		return this->startOnStair;
	}
	bool CheckIsOnStair() {
		return this->isOnStair;
	}
	bool CheckCollideWithStair() {
		return this->isColliceWithStair;
	}
	void SetStartStepOnStair() {
		this->startOnStair = true;
	}

	int Untouch() {
		return untouchable;
	}

	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	int GetHp() { return this->hp; }
	void SetHP(float hp) {
		this->hp = hp;
		if (this->hp > SIMON_HP)
			this->hp = SIMON_HP;
		else if (this->hp < 0)
			this->hp = 0;
	}
	void AddHP(int point) {
		this->hp += point;
		SetHP(hp);
	}

	int GetEnergy() { return this->energy;}
	void SetEnery(int energy) {
		this->energy = energy;
		if (this->energy > SIMON_ENERY)
			this->energy = SIMON_ENERY;
		else if (this->energy < 0)
			this->energy = 0;
	}
	void AddEnery(int point) {
		this->energy += point;
		SetEnery(energy);
	}
	
};