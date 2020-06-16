#pragma once
#include"Enemy.h"

#define BAT_BBOX_HEIGHT 32
#define BAT_BBOX_WIDTH 32

#define BAT_FLY_SPEED_X  0.15f
#define BAT_FLY_SPEED_Y  0.15f

#define ACTIVE_BAT_X 100
#define ACTIVE_BAT_Y 150

#define BAT_OY_HEIGHT 100 //độ cao sóng  sin khi bat di chuyen

#define BAT_ANI_IDLE 0
#define BAT_ANI_FLY 1
enum class BATSTATE {
	IDLE,
	FLY
};

class Bat :public Enemy
{
private:
	float oy; // tọa độ oy bat sẽ di chuyển quanh trục này ( =y)
	BATSTATE state;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt,Scene*scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetSpriteBox(float& _width, float& _height) {
		_width = BAT_BBOX_WIDTH;
		_height = BAT_BBOX_HEIGHT;
	};
	void SetOy() {
		this->oy = this->y;
	}
	void SetState(BATSTATE state);
	Bat();
};

