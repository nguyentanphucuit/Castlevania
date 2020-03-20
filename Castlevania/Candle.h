#pragma once
#include "GameObject.h"

#define CANDLE_WIDTH 16
#define CANDLE_HEIGHT 32

#define CANDLE_ANI_BURN 0

class CCandle : public CGameObject
{
	bool isDestroy = false;
public:
	CCandle() {
		AddAnimation("CANDLE_ANI_BURN");
	}
	void SetDestroy() { this->isDestroy = true; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

