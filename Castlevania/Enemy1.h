#pragma once
#include"Enemy.h"

#define BAT_BBOX_HEIGHT 32
#define BAT_BBOX_WIDTH 32

#define BAT_FLY_SPEED_X  0.15f
#define BAT_FLY_SPEED_Y  0.02f

#define BAT_OY_HEIGHT 30 //độ cao sóng  sin khi bat di chuyen

class Bat :public Enemy
{
private:
	float oy; // tọa độ oy bat sẽ di chuyển quanh trục này ( =y)
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene * scene,vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetSpriteBox(float& _width, float& _height) {
		_width = BAT_BBOX_WIDTH;
		_height = BAT_BBOX_HEIGHT;
	};
	void SetOy() {
		this->oy = this->y;
	}
	Bat();
	Bat(float oy);
	~Bat();
};

