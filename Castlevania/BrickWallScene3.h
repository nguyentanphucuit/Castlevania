#pragma once
#include "GameObject.h"
#include "ItemFactory.h"

#define BRICKWALLS3_WIDTH  30
#define BRICKWALLS3_HEIGHT 28



class CBrickWallS3 : public CGameObject
{
	EItem item;
public:
	CBrickWallS3() {
		AddAnimation("BRICKWALL_ANI_S3");
		this->item = EItem::CHICKEN;
	}
	void SetDestroy() { this->isDestroy = true; }

	bool IsDestroyed() { return isDestroy; }

	EItem GetItem() { return this->item; }
	void SetItem(EItem e) { this->item = e; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

