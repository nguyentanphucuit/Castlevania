#include "Goomba.h"

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBASTATE::DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else 	
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, scene);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	vx = 0.2f;
	
	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBASTATE::DIE) {
		ani = GOOMBA_ANI_DIE;
	}

	animations[ani]->Render(nx,x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(GOOMBASTATE state)
{
	
	switch (state)
	{
		case GOOMBASTATE::WALKING:
			y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			break;
		case  GOOMBASTATE::DIE:
			vx = -GOOMBA_WALKING_SPEED;
	}

}
