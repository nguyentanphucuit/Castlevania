#include "Skeleton.h"
#include "define.h"


void Skeleton::Render()
{
	if (isDestroy) {
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void Skeleton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + SKELETON_BBOX_WIDTH;
	b = t + SKELETON_BBOX_HEIGHT;
}

void Skeleton::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	if (isDestroy) {
		return;
	}

	//vx = nx == DIRECTION::RIGHT ? this->vx = SKELETON_VX : this->vx = -SKELETON_VX;


	
	vx = 0.2f;


		
	if (y != 450 && !checkup) {
		up = true;
		checkup = true;
	}
	else 
		up = false;

	if (up) vy = -.35f;
	else vy = .35f;

	/*vy += 0.002*dt;
	
	x += dx;
	y = 20 * sin(x * 0.02f) + oy;*/
	Weapon::Update(dt, scene, coObject);

}

