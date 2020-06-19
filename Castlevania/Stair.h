#pragma once
#include "HiddenObject.h"
class Stair : public HiddenObject
{
	int direction; 
	bool isActive = false; // co with somthing trigger

public:
	void SetActive(bool flag) {
		this->isActive = flag;
	}
	int GetDirection() {
		return this->direction;
	}
	void SetDirection(int dir) {
		this->direction = dir;
	}
	bool CheckActive() {
		return this->isActive;
	}
	Stair() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL) {};
};

