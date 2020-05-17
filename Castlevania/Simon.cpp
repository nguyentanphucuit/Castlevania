#include <algorithm>
#include "debug.h"
#include "SIMON.h"
#include "Game.h"
#include "Ground.h"
#include "Torch.h"
#include "ItemFactory.h"
#include "WeaponFactory.h"
#include "HMoney.h"
#include "Entrance.h"
#include "HMoney.h"
#include "RetroGrade.h"

CSIMON::CSIMON() : CGameObject() {
	level = SIMON_LEVEL_BIG;
	untouchable = 0;
	this->fight_start = 0;
	upgrade_start = 0;
	state = SIMONSTATE::IDLE; 
	whip = new Whip(); 

	this->currentWeapon = EWeapon::NONE;

	AddAnimation("SIMON_ANI_IDLE");	
	AddAnimation("SIMON_ANI_WALKING");
	AddAnimation("SIMON_ANI_SIT");
	AddAnimation("SIMON_ANI_STAND_ATTACK",false);
	AddAnimation("SIMON_ANI_SIT_ATTACK",false);
	AddAnimation("SIMON_ANI_IDLE_UPWHIP"); 
}
void CSIMON::Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT> *coObjects)
{
	

	// Calculate dx, dy 
	
	CGameObject::Update(dt,scene);

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
		
		

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*>(e->obj)) { 
				isOnGround = true;
				
				if (e->ny != 0) { 
					
					if (GetState() == SIMONSTATE::JUMP) {
						SetState(SIMONSTATE::IDLE);
					}
					if (this->state == SIMONSTATE::FIGHT_STAND)
					{
						vx = 0;
					}
					if (ny != 0) vy = 0;
					if (state != SIMONSTATE::ENTERENTRANCE) {
						if (nx != 0) vx = 0;
					}
				}
				if (state == SIMONSTATE::ENTERENTRANCE) { break; }
				
				

			}
			else
			{
				if (dynamic_cast<Item*>(e->obj)) {
					Item* item = dynamic_cast<Item*>(e->obj);
					// kiểm tra loại Item đã bị huỷ chưa
					if (!item->IsDestroy()) {
						item->SetDestroy();
					}
					
					if (dynamic_cast<IWhip*>(item)) {
						this->SetState(SIMONSTATE::UPWHIP);
					}
					if (dynamic_cast<IDagger*>(item)) {
						this->currentWeapon = EWeapon::Dagger;
					}
				}
				else if (dynamic_cast<RetroGrade*>(e->obj)) {
					this->SetState(SIMONSTATE::RETROGRADE);
				}	
				else if (dynamic_cast<Entrance*>(e->obj)) {
					auto entrance = dynamic_cast<Entrance*> (e->obj);
					entrance->SetDestroy();
					this->SetState(SIMONSTATE::ENTERENTRANCE);
				}
				else if (dynamic_cast<HMoney*>(e->obj)) {
					auto hmoney = dynamic_cast<HMoney*>(e->obj);
					hmoney->SetDestroy();
					if (dynamic_cast<PlayScene*>(scene)) {
						auto pScene = dynamic_cast<PlayScene*>(scene);
						pScene->SpawnObject(hmoney->GetItem());
					}
				}
				
				if (e->nx!=0) 
					x += dx;
				if (e->ny != 0)
					y += dy;
				
			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	// xử lý va chạm simon và các items
	for (size_t i = 0; i < coObjects->size(); i++) {
		if (this->isColliding(coObjects->at(i))) {
			if (dynamic_cast<Item*>(coObjects->at(i))) {
				Item* item = dynamic_cast<Item*>(coObjects->at(i));
				if(!item->IsDestroy()){
					if (dynamic_cast<IWhip*>(item)) {
						this->SetState(SIMONSTATE::UPWHIP);
					}
					if (dynamic_cast<IDagger*>(item)) {
						this->currentWeapon = EWeapon::Dagger;
					}
					item->SetDestroy();
				}
			}
		}
	}

	if (this->fight_start!=0) // có đánh mới cần set
	{
		if (!this->spawnWeapon) {
			if (this->state == SIMONSTATE::FIGHT_SIT)
			{
				whip->SetPosition(this->x - 1.5 * SIMON_SPRITE_WIDTH, this->y + SIMON_SPRITE_HEIGHT * 0.25); //đặt tọa độ whip theo vị trí simon
			}
			else
			{
				whip->SetPosition(this->x - 1.5 * SIMON_SPRITE_WIDTH, this->y); 
			}
			whip->SetNxDirection(this->nx);
			whip->Update(dt, scene, coObjects);
		}
		else if (!isSpawnWeapon) {
			auto weapon= WeaponFactory::SpawnWeapon<Weapon*>(this->currentWeapon);
			weapon->SetPosition(this->x, this->y+10);
			weapon->SetNx(this->nx);
			if (dynamic_cast<PlayScene*>(scene)) {
				PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
				pScene->SpawnObject(weapon);
				isSpawnWeapon = true;
			}
		}
		
	}
}

void CSIMON::Render()
{
	int ani = 0;
	switch (state)
	{	
	case SIMONSTATE::IDLE:
		ani = SIMON_ANI_IDLE;
		break;
	case SIMONSTATE::ENTERENTRANCE:
	case SIMONSTATE::WALKING_RIGHT:
		ani = SIMON_ANI_WALKING;
		break;		
	case SIMONSTATE::RETROGRADE:
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
	case SIMONSTATE::UPWHIP:
		ani = SIMON_ANI_UP_WHIP;
		break;
	case SIMONSTATE::DIE:
		break;
	case SIMONSTATE::FIGHT_STAND:
		ani = SIMON_ANI_STAND_ATTACK;
		break;
	case SIMONSTATE::FIGHT_SIT:
		ani = SIMON_ANI_SIT_ATTACK;
		break;
	default:
		break;
	}
	
	if (this->fight_start!=0 && !this->spawnWeapon)
	{
		whip->Render();
	}
	//DebugOut(L"SIMON state=%d \n", (int)state);
	int alpha = 255;
	if (untouchable) alpha = 128;

	animations[ani]->Render(nx,x, y, alpha);

	//RenderBoundingBox();
}

void CSIMON::SetState(SIMONSTATE state)
{


	switch (state)
	{
	
	case SIMONSTATE::ENTERENTRANCE:
		this->ResetAttack();
		nx = 1;
		vx = SIMON_WALKING_SPEED / 2;
		break;
	case SIMONSTATE::RETROGRADE:
		isTouchRetroGrade = true;
		vx = 0;
		break;
	case SIMONSTATE::WALKING_RIGHT:
		isTouchRetroGrade = false;
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMONSTATE::WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMONSTATE::JUMP: // nhảy rồi thì chắc ăn k chạm đất
		isOnGround = false;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMONSTATE::IDLE:
		vx = 0;
		break;
	case SIMONSTATE::DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMONSTATE::UPWHIP:
		whip->Upgrade();
		this->ResetAttack();
		this->upgrade_start = GetTickCount();
		vx = 0;
		break;
	case SIMONSTATE::SIT:
		vx = 0; 
		break;
	case SIMONSTATE::FIGHT_STAND:
		vx = this->state == SIMONSTATE::IDLE || this->state == SIMONSTATE::WALKING_LEFT
			|| this->state == SIMONSTATE::WALKING_RIGHT ? 0 : vx;
		this->fight_start = GetTickCount(); 
		break;
	case SIMONSTATE::FIGHT_SIT:
		vx = 0;
		this->fight_start = GetTickCount();
		break;
	}

	this->state = state;

}

void CSIMON::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 17;
	top = y; 

	right = left + SIMON_BBOX_WIDTH;
	bottom = top + SIMON_BBOX_HEIGHT;

}

