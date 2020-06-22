#pragma once
#include "GameObject.h"

enum class EWeapon;

class Weapon:public CGameObject
{
private:
	EWeapon _eWeapon;
public:
	virtual void Render() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	void SetNx(DIRECTION nx) { this->nx = nx; }
};

