#pragma once
#include"Enemy.h"
#define BLACKKNIGHT_BBOX_WIDTH 32
#define BLACKKNIGHT_BBOX_HEIGHT 60

#define BLACKKNIGHT_GRAVITY			0.002f
#define BLACKKNIGHT_WALKING_SPEED			0.10f


class BlackKnight :public Enemy
{
private:
	int left = false;
	int _endPos;
	int _startPos;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	
	virtual void GetSpriteBox(float& _width, float& _height) {
		_width = BLACKKNIGHT_BBOX_WIDTH;
		_height = BLACKKNIGHT_BBOX_WIDTH 
			;
	};

	void Area(int startPos, int endPos);
	BlackKnight();
};



