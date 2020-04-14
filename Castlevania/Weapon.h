#pragma once
#include "GameObject.h"
#include "define.h"
#include "PlayScene.h"
#include "Torch.h"


class Weapon:public CGameObject
{
public:
	virtual void Render() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	void SetNx(int nx) { this->nx = nx; }
};

