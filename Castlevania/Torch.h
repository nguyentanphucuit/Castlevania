#pragma once
#include "GameObject.h"


#define TORCH_WIDTH  32
#define TORCH_HEIGHT 64

#define TORCH_ANI_BURN 0
class CTorch : public CGameObject
{
	bool isDestroy = false;
public:
	CTorch() {
		AddAnimation("TORCH_ANI_BURN");
	}
	void SetDestroy() { this->isDestroy = true; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

