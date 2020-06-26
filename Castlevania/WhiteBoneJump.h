#pragma once
#include"HiddenObject.h"
class WhiteBoneJump :public HiddenObject
{
	int direction;
public:
	WhiteBoneJump() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
	void SetDirection(int dir) {
		this->direction = dir;
	}
	int GetDirection() { return direction; }
};

