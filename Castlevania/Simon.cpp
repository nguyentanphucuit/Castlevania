#include <algorithm>
#include "debug.h"

#include "SIMON.h"
#include "Game.h"
#include "Goomba.h"
#include "Brick.h"

void CSIMON::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=SIMONSTATE::DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBASTATE::DIE)
					{
						goomba->SetState(GOOMBASTATE::DIE);
						vy = -SIMON_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						if (goomba->GetState()!= GOOMBASTATE::DIE)
						{
							if (level > SIMON_LEVEL_SMALL)
							{
								level = SIMON_LEVEL_SMALL;
								StartUntouchable();
							}
							else 
								SetState(SIMONSTATE::DIE);
						}
					}
				}
			}
			
			if (dynamic_cast<CBrick*>(e->obj)) {
				if (e->ny != 0) { // kiểm tra va chạm trục y có va chạm trục y nhảy vào đây
					touchBrick = true;
					if (GetState() == SIMONSTATE::JUMP) {
						SetState(SIMONSTATE::IDLE);
					}
				}
				
				// cần xét kỹ phương va chạm

			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSIMON::Render()
{
	int ani=0; // mặc định để chặn lỗi do chưa có ani của state walking left
	switch (state)
	{	
	case SIMONSTATE::IDLE:
		ani = SIMON_ANI_IDLE;
		break;
	case SIMONSTATE::WALKING_RIGHT:
		ani = SIMON_ANI_WALKING;
		break;			
	case SIMONSTATE::WALKING_LEFT:
		ani = SIMON_ANI_WALKING;
		break;
	case SIMONSTATE::SIT:
		ani = SIMON_ANI_SIT;
		break;
	case SIMONSTATE::JUMP:
		ani = SIMON_ANI_SIT;
		break;
	case SIMONSTATE::DIE:
		break;
	default:
		break;
	}
	
	DebugOut(L"SIMON state=%d \n", (int)state);
	int alpha = 255;
	if (untouchable) alpha = 128;

	animations[ani]->Render(nx,x, y, alpha);

	RenderBoundingBox();
}

void CSIMON::SetState(SIMONSTATE state)
{


	switch (state)
	{
	case SIMONSTATE::WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMONSTATE::WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMONSTATE::JUMP: // nhảy rồi thì chắc ăn k chạm đất
		touchBrick = false;
		vy = -SIMON_JUMP_SPEED_Y;
		
		break;
	case SIMONSTATE::IDLE:
		vx = 0;
		break;
	case SIMONSTATE::DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMONSTATE::SIT:
		vx = 0; // vx vận tốc phương x
		//nx=0; k cần xét nx vì khi bấm trái phải đã set nx ở 2 state phía trên
		break;
	}
	this->state = state;

}

void CSIMON::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level==SIMON_LEVEL_BIG)
	{
		right = x + SIMON_BIG_BBOX_WIDTH;
		bottom = y + SIMON_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + SIMON_SMALL_BBOX_WIDTH;
		bottom = y + SIMON_SMALL_BBOX_HEIGHT;
	}
}

