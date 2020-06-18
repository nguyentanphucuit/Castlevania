#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include"Scene.h"
#include "Sprites.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define PI 3.14159265359

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

struct CellIndex {
	int x;
	int y;
	CellIndex(int x, int y) :x(x), y(y) {};
};


class CGameObject
{
public:

	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	DIRECTION nx;	 

	DWORD dt; 
	bool isActive; // check object in grid
	vector<LPANIMATION> animations;
	bool isDestroy = false;
	CellIndex cellIndex = { -1,-1 };
public: 
	void SetCellIndex(int cellX, int cellY) {
		CellIndex cellIndex = { cellX,cellY };
		this->cellIndex = cellIndex;
	}
	CellIndex GetCellIndex() {
		return cellIndex;
	}
	void SetActive() { isActive = true; };
	bool CheckActive() { return isActive; }
	void SetDestroy() { this->isDestroy = true; }
	bool IsDestroy() { return isDestroy; }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);


	// kiểm tra object hiện tại có đang va chạm với object a hay không
	bool isColliding(LPGAMEOBJECT a);
	// thuat toan xu ly va cham AABB
	bool AABB(float l, float t, float r, float b, float l1, float t1, float r1, float b1);

	void AddAnimation(string aniId,bool isLoop=true);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	//virtual void SetState(int state) { this->state = state; }


	~CGameObject();
};

