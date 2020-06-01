#pragma once
#include "HiddenObject.h"
class Stair : public HiddenObject
{
	int direction; // hướng của cầu thang
	bool isActive = false; // dùng để đánh dấu simon đang va chạm trigger nào

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

