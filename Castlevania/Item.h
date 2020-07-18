#pragma once

#include"GameObject.h"

#define ITEM_GRAVITY    0.002f
#define ITEM_HIDING		300 

enum class ITEMSTATE
{
	HIDE,
	SHOW,
	DISTROYING,
	DISTROYED
};

class Item :public CGameObject
{
protected:
	unsigned int hp;
	unsigned int score;
	unsigned int heart;
	DWORD time_wait;
public:

	Item() : CGameObject() {
		time_wait = GetTickCount();
		this->heart = 0;
		
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	int GetHeartPoint() {
		return this->heart;
	}
	int GetScore() { return this->score; }
	int GetHP() { return this->hp; }
};

