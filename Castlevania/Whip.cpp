#include "Whip.h"

void Whip::Render()
{
	int ani;
	switch (state)
	{			
	case NORMAL:
		ani = WHIP_ANI_NORMAL;
		break;
	case CHAIN:
		ani = WHIP_ANI_CHAIN;
		break;
	case MORINGSTAR:
		ani = WHIP_ANI_MORNINGSTAR;
		break;
	}
	animations[ani]->Render(nx, x, y);
}

void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
}

void Whip::SetState(WHIPSTATE state)
{
	switch (state)
	{	
	case NORMAL:
		break;
	case CHAIN:
		break;
	case MORINGSTAR:
		break;
	default:
		break;
	}
	this->state = state;
}
