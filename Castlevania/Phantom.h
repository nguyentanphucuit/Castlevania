#pragma once
#include"Enemy.h"

#define PHANTOM_BBOX_HEIGHT 32
#define PHANTOM_BBOX_WIDTH 32

#define PHANTOM_FLY_SPEED_X  0.15f
#define PHANTOM_FLY_SPEED_Y  0.15f

#define ACTIVE_PHANTOM_X 100
#define ACTIVE_PHANTOM_Y 150

#define PHANTOM_OY_HEIGHT 100 //độ cao sóng  sin khi bat di chuyen

#define PHANTOM_ANI_IDLE 0
#define PHANTOM_ANI_FLY 1
enum class PHANTOMSTATE {
	IDLE,
	FLY
};

class Phantom :public Enemy
{
private:
	float oy; // tọa độ oy bat sẽ di chuyển quanh trục này ( =y)
	PHANTOMSTATE state;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetSpriteBox(float& _width, float& _height) {
		_width = PHANTOM_BBOX_WIDTH;
		_height = PHANTOM_BBOX_HEIGHT;
	};
	void SetOy() {
		this->oy = this->y;
	}
	void SetState(PHANTOMSTATE state);
	Phantom();
};

