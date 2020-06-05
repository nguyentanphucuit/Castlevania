#pragma once
#include "GameObject.h"
#include "ItemFactory.h"

#define CANDLE_WIDTH  16
#define CANDLE_HEIGHT 32
#define CANDLE_ANI_BURN 0


class CCandle : public CGameObject
{
	EItem item;
public:
	CCandle() {
		AddAnimation("CANDLE_ANI_BURN");
		this->item = EItem::HEART;
	}
	void SetDestroy() { this->isDestroy = true; }

	bool IsDestroyed() { return isDestroy; }

	EItem GetItem() { return this->item; }
	void SetItem(EItem e) { this->item = e; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

