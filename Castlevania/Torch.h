#pragma once
#include "GameObject.h"
#include"ItemFactory.h"

#define TORCH_WIDTH  32
#define TORCH_HEIGHT 64
#define TORCH_ANI_BURN 0


class CTorch : public CGameObject
{
	//item của torch đọc từ file vì từng torch có các item có thể khác nhau
	EItem item;// item chứa trong torch
public:
	CTorch() {
		AddAnimation("TORCH_ANI_BURN");
		this->item = EItem::HEART;
	}
	void SetDestroy() { this->isDestroy = true; }
	//Xem torch có bị hủy chưa
	bool IsDestroyed() { return isDestroy; }

	EItem GetItem() { return this->item; }
	void SetItem(EItem e) { this->item = e; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

