#pragma once
#include "GameObject.h"
#define TIME_CO		200
enum class EWeapon;

class Weapon:public CGameObject
{
private:
	EWeapon _eWeapon;
	DWORD timeCo;
	bool isCoEnemy = false;

protected:
	int damage = 1;
public:
	virtual void Render() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	void SetNx(DIRECTION nx) { this->nx = nx; }
	int getDamage() { return this->damage; }
};

