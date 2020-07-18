#pragma once
#include "GameObject.h"
#include "ItemFactory.h"

#define BRICKWALL_WIDTH  33
#define BRICKWALL_HEIGHT 28

#define BRICKWALL2_ANI 0

class CBrickWall : public CGameObject
{
	EItem item;
public:
	CBrickWall() {
		AddAnimation("BRICKWALL2_ANI");
	}
	void SetDestroy() { this->isDestroy = true; }

	bool IsDestroyed() { return isDestroy; }

	EItem GetItem() { return this->item; }
	void SetItem(EItem e) { this->item = e; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

