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
#include "HCrown.h"
#include "RetroGrade.h"
#include "SwitchScene.h"
#include "Stair.h"
#include "Platform.h"
#include "Enemy.h"
#include "Dual.h"

CSIMON::CSIMON() : CGameObject() {
	level = SIMON_LEVEL_BIG;
	untouchable = 0;
	hp = 2;
	this->energy = 5;
	this->fight_start = 0;
	upgrade_start = 0;
	state = SIMONSTATE::IDLE;
	whip = new Whip();

	this->currentWeapon = EWeapon::NONE;

	AddAnimation("SIMON_ANI_IDLE");
	AddAnimation("SIMON_ANI_WALKING");
	AddAnimation("SIMON_ANI_SIT");
	AddAnimation("SIMON_ANI_STAND_ATTACK", false);
	AddAnimation("SIMON_ANI_SIT_ATTACK", false);
	AddAnimation("SIMON_ANI_IDLE_UPWHIP");
	AddAnimation("SIMON_ANI_STEP_UPSTAIR");
	AddAnimation("SIMON_ANI_IDLE_UPSTAIR");
	AddAnimation("SIMON_ANI_IDLE_DOWNSTAIR");
	AddAnimation("SIMON_ANI_STEP_DOWNSTAIR");
	AddAnimation("SIMON_ANI_UPSTAIR_ATTACK", false);
	AddAnimation("SIMON_ANI_DOWNSTAIR_ATTACK", false);
	AddAnimation("SIMON_ANI_DEFLECT");
	AddAnimation("SIMON_ANI_DIE", false); 
}

void CSIMON::HandleFirstStepOnStair()
{
	if (onStairDirection == STAIRDIRECTION::DEFAULT) {
		DebugOut(L"Return \n");
		return;
	}
	//reset vx vy remain from last state
	this->vx = 0;
	this->vy = 0;
	if (state == SIMONSTATE::WALKING_LEFT)
	{
		int a = 2;
	}
	//DebugOut(L"HandleFirstStepOnStair \n");
	//up right first step

	if (onStairDirection == STAIRDIRECTION::UPRIGHT) {
		//DebugOut(L"Simon x=%f y=%f \n", this->x, this->y);

		if (stairPos.x - this->x > SIMON_UPSTAIR_RIGHT_OFFSET) {
			SetState(SIMONSTATE::WALKING_RIGHT);
			return;
		}
		else if (stairPos.x - this->x < SIMON_UPSTAIR_RIGHT_OFFSET - STEP_STAIR) {

			SetState(SIMONSTATE::WALKING_LEFT);
			return;
		}
		else {
			if (state == SIMONSTATE::WALKING_LEFT) {
				if (nx == DIRECTION::LEFT) nx = DIRECTION::RIGHT;
				else if (nx == DIRECTION::RIGHT) nx = DIRECTION::LEFT;
			}
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
			//DebugOut(L"Step x=%f y=%f \n", this->LastStepOnStairPos.x, this->LastStepOnStairPos.y);
			this->SetState(SIMONSTATE::UP_STAIR_RIGHT);
		}
	}
	else if (onStairDirection == STAIRDIRECTION::UPLEFT) {
		//DebugOut(L"Simon x=%f y=%f \n", this->x, this->y);

		if (stairPos.x - this->x < SIMON_UPSTAIR_LEFT_OFFSET) {

			SetState(SIMONSTATE::WALKING_LEFT);
			return;
		}
		else if (stairPos.x - this->x > SIMON_UPSTAIR_LEFT_OFFSET + STEP_STAIR) {

			SetState(SIMONSTATE::WALKING_RIGHT);
			return;
		}
		else {
			if (state == SIMONSTATE::WALKING_RIGHT) {
				if (nx == DIRECTION::LEFT) nx = DIRECTION::RIGHT;
				else if (nx == DIRECTION::RIGHT) nx = DIRECTION::LEFT;
			}
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
			//DebugOut(L"Step x=%f y=%f \n", this->LastStepOnStairPos.x, this->LastStepOnStairPos.y);
			this->SetState(SIMONSTATE::UP_STAIR_RIGHT);
		}
	}
	else if (onStairDirection == STAIRDIRECTION::DOWNLEFT)
	{
		if (stairPos.x - this->x < SIMON_DOWNSTAIR_LEFT_OFFSET) {

			SetState(SIMONSTATE::WALKING_LEFT);
			return;
		}
		else if (stairPos.x - this->x > SIMON_DOWNSTAIR_LEFT_OFFSET + STEP_STAIR) {

			SetState(SIMONSTATE::WALKING_RIGHT);
			return;
		}
		else {
			if (state == SIMONSTATE::WALKING_RIGHT) {
				if (nx == DIRECTION::LEFT) nx = DIRECTION::RIGHT;
				else if (nx == DIRECTION::RIGHT) nx = DIRECTION::LEFT;
			}
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
			//DebugOut(L"First Step x=%f y=%f \n", this->LastStepOnStairPos.x, this->LastStepOnStairPos.y);
			this->SetState(SIMONSTATE::DOWN_STAIR_LEFT);
		}
	}
	else if (onStairDirection == STAIRDIRECTION::DOWNRIGHT)
	{
		if (stairPos.x - this->x > SIMON_DOWNSTAIR_RIGHT_OFFET) {

			SetState(SIMONSTATE::WALKING_RIGHT);
			return;
		}
		else if (stairPos.x - this->x < SIMON_DOWNSTAIR_RIGHT_OFFET - STEP_STAIR) {

			SetState(SIMONSTATE::WALKING_LEFT);
			return;
		}
		else {
			if (state == SIMONSTATE::WALKING_LEFT) {
				if (nx == DIRECTION::LEFT) nx = DIRECTION::RIGHT;
				else if (nx == DIRECTION::RIGHT) nx = DIRECTION::LEFT;
			}
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
			//DebugOut(L"First Step x=%f y=%f \n", this->LastStepOnStairPos.x, this->LastStepOnStairPos.y);
			this->SetState(SIMONSTATE::DOWN_STAIR_RIGHT);
		}
	}
}

void CSIMON::HandlePerStepOnStair()
{
	if (this->state == SIMONSTATE::UP_STAIR_RIGHT) {
		DebugOut(L"Up right \n ");
		if (this->x - LastStepOnStairPos.x > SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y > SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y - SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x + SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMONSTATE::UP_STAIR_IDLE);
				this->isOnStair = true;
				//DebugOut(L"Up right \n ");
			}

		}
	}
	else if (this->state == SIMONSTATE::UP_STAIR_LEFT) {
		if (this->x - LastStepOnStairPos.x < SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y > SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y - SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x - SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMONSTATE::UP_STAIR_IDLE);
				this->isOnStair = true;
				//	DebugOut(L" x=%f y=%f \n", this->x, this->y);
			}

		}
	}
	else if (this->state == SIMONSTATE::DOWN_STAIR_LEFT)
	{
		if (LastStepOnStairPos.x - this->x > SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y < SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y + SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x - SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMONSTATE::DOWN_STAIR_IDLE);
				this->isOnStair = true;
				//DebugOut(L" DOWN left x=%f y=%f \n", this->x, this->y);
			}

		}
	}
	else if (this->state == SIMONSTATE::DOWN_STAIR_RIGHT)
	{
		if (this->x - LastStepOnStairPos.x > SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y < SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y + SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x + SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMONSTATE::DOWN_STAIR_IDLE);
				this->isOnStair = true;
				//DebugOut(L" DOWN Right x=%f y=%f \n", this->x, this->y);
			}

		}
	}
}

void CSIMON::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{


	// Calculate dx, dy 
	CGameObject::Update(dt, scene);


	DebugOut(L"This-> state=%d \n", this->state);
	//DebugOut(L"This-> stair dir =%d \n", this->onStairDirection);
	if (this->state == SIMONSTATE::DIE)
	{
		return;
	}
	if (this->startOnStair) {
		if (!this->isFirstStepOnStair)
			HandleFirstStepOnStair();
		else {
			if (this->onStairDirection == STAIRDIRECTION::UPRIGHT)
				SetState(SIMONSTATE::UP_STAIR_RIGHT);
			else if (this->onStairDirection == STAIRDIRECTION::UPLEFT)
			{
				SetState(SIMONSTATE::UP_STAIR_LEFT);
			}
			else if (this->onStairDirection == STAIRDIRECTION::DOWNLEFT)
			{
				SetState(SIMONSTATE::DOWN_STAIR_LEFT);
			}
			else if (this->onStairDirection == STAIRDIRECTION::DOWNRIGHT)
			{
				SetState(SIMONSTATE::DOWN_STAIR_RIGHT);
			}
		}
	}
	this->HandlePerStepOnStair();
	// Simple fall down
	if (!this->startOnStair
		&& !this->isOnStair
		&& state != SIMONSTATE::UP_STAIR_IDLE
		&& state != SIMONSTATE::DOWN_STAIR_IDLE

		)
	{
		vy += SIMON_GRAVITY * dt;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMONSTATE::DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (ny < 0)
		{
			y += min_ty * dy + ny * 0.4f;
		}

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*>(e->obj)) {
			
			
				if (this->isOnStair) {
					x += dx;
					y += dy;
					continue;
				}
				if (e->nx == -1) {
					isOnPlatform = false;
				}
				if (e->ny == -1) {
					isOnGround = true;
					isOnPlatform = false;
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
					/*if (this->hp == 0)
					{
						this->SetState(SIMONSTATE::DIE);
						this->isOnStair = false;
						break;
					}*/
				}
				else if (e->ny == 1)
				{
					y += dy;
				}

				if (e->nx != 0 && ny != -1) {
					y += dy;
				}
				if (state == SIMONSTATE::ENTERENTRANCE) { break; }


			}
			else if (dynamic_cast<Enemy*>(e->obj)) {
				Enemy* enemy = dynamic_cast<Enemy*> (e->obj);

				if (this->isColliding(enemy))
				{
					if (untouchable_start == 0) {

						DebugOut(L"Collice with enemy \n", this->vy, this->vx);
						if (!this->isOnStair)
						{
							this->SetState(SIMONSTATE::DEFLECT);
						}
						if (untouchable != 1) {
							this->AddHP(-2);
							StartUntouchable();
						}
					}

				}
			}
			else if (dynamic_cast<SwitchScene*>(e->obj)) {
				auto switchScene = dynamic_cast<SwitchScene*>(e->obj);
				if (dynamic_cast<PlayScene*> (scene)) {
					auto pScene = dynamic_cast<PlayScene*>(scene);
					int id = switchScene->GetSceneID();
					pScene->SwitchPScene(id);
				}
			}
			else if (dynamic_cast<CPlatform*>(e->obj)) {
				isOnPlatform = true;
				CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
				if (e->ny != 0) {
					if (GetState() == SIMONSTATE::JUMP && !isOnGround) {
						SetState(SIMONSTATE::IDLE);
					}
					if (ny != 0) vy = 0;
				}
				this->x += platform->vx*dt*3.f;
				
				DebugOut(L"x SIMON = %f\n", x);
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
						this->currentWeapon = EWeapon::NONE;
					}
					if (dynamic_cast<IDagger*>(item)) {
						this->currentWeapon = EWeapon::DAGGER;

					}
					if (dynamic_cast<IAXE*>(item)) {
						this->currentWeapon = EWeapon::AXE;
					}
					if (dynamic_cast<IFireBomb*>(item)) {
						this->currentWeapon = EWeapon::FIREBOMB;
					}
					if (dynamic_cast<IBoomerang*>(item)) {
						this->currentWeapon = EWeapon::BOOMERANG;
					}
					if (dynamic_cast<IStopWatch*>(item)) {
						this->currentWeapon = EWeapon::STOPWATCH;
					}
					if (dynamic_cast<IInvisible*>(item)) {
						StartUntouchable();
					}
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
				else if (dynamic_cast<HCrown*>(e->obj)) {
					auto hcrown = dynamic_cast<HCrown*>(e->obj);
					hcrown->SetDestroy();
					if (dynamic_cast<PlayScene*>(scene)) {
						auto pScene = dynamic_cast<PlayScene*>(scene);
						pScene->SpawnObject(hcrown->GetItem());
					}
				}


				if (e->nx != 0)
					x += dx;
				if (e->ny != 0) {

					y += dy;


				}


			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	// xử lý va chạm simon và các items
	for (size_t i = 0; i < coObjects->size(); i++) {
		if (dynamic_cast<Stair*>(coObjects->at(i))) {
			Stair* f = dynamic_cast<Stair*> (coObjects->at(i));

			if (this->isColliding(f))
			{
				if (!this->isColliceWithStair) {
					if (this->isOnStair) {

						SetState(SIMONSTATE::IDLE);
						this->isOnStair = false;
						this->startOnStair = false;
						this->isFirstStepOnStair = false;
						return;
					}
					this->isColliceWithStair = true;
					this->onStairDirection = static_cast<STAIRDIRECTION>(f->GetDirection());
					this->stairPos = { f->x,f->y };
					f->SetActive(true);
					return;
				}
			}
			else if (f->CheckActive())
			{
				f->SetActive(false);
				this->isColliceWithStair = false;
				if (!this->isOnStair)

					this->onStairDirection = STAIRDIRECTION::DEFAULT; //reset
			}
		}
		else if (this->isColliding(coObjects->at(i))) {
			if (dynamic_cast<Item*>(coObjects->at(i))) {
				Item* item = dynamic_cast<Item*>(coObjects->at(i));
				if (!item->IsDestroy()) {
					if (dynamic_cast<IWhip*>(item)) {
						this->SetState(SIMONSTATE::UPWHIP);
						this->currentWeapon = EWeapon::NONE;
					}
					if (dynamic_cast<IDagger*>(item)) {
						this->currentWeapon = EWeapon::DAGGER;
					}
					if (dynamic_cast<IAXE*>(item)) {
						this->currentWeapon = EWeapon::AXE;
					}
					if (dynamic_cast<IFireBomb*>(item)) {
						this->currentWeapon = EWeapon::FIREBOMB;
					}
					if (dynamic_cast<IBoomerang*>(item)) {
						this->currentWeapon = EWeapon::BOOMERANG;
					}
					if (dynamic_cast<IStopWatch*>(item)) {
						this->currentWeapon = EWeapon::STOPWATCH;
					}
					if (dynamic_cast<IInvisible*>(item)) {
						StartUntouchable();
					}
					item->SetDestroy();
				}
			}
		}
		if (dynamic_cast<Enemy*>(coObjects->at(i))) {
			Enemy* enemy = dynamic_cast<Enemy*> (coObjects->at(i));

			if (this->isColliding(enemy))
			{
				if (untouchable_start == 0) {

					DebugOut(L"Collice with enemy \n", this->vy, this->vx);
					if (!this->isOnStair)
					{
						this->SetState(SIMONSTATE::DEFLECT);
					}
					if (untouchable != 1) {
						this->AddHP(-2);
						StartUntouchable();
					}
				}

			}
		}
		if (dynamic_cast<Dual*>(coObjects->at(i))) {
			Dual* dual = dynamic_cast<Dual*> (coObjects->at(i));
			if (this->isColliding(dual)) {
				isStairDual = true;
				if (this->onStairDirection == STAIRDIRECTION::UPLEFT) {
					this->onStairDirection = STAIRDIRECTION::UPRIGHT;
				}else if (this->onStairDirection == STAIRDIRECTION::DOWNLEFT) {
					this->onStairDirection = STAIRDIRECTION::DOWNRIGHT;
				}
			}
			
			
		}
		if (this->fight_start != 0) // có đánh mới cần set
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
				auto weapon = WeaponFactory::SpawnWeapon<Weapon*>(currentWeapon);
				weapon->SetPosition(this->x, this->y + 10);
				weapon->SetNx(this->nx);
				if (dynamic_cast<WStopWatch*>(weapon)){
					auto sw = dynamic_cast<WStopWatch*>(weapon);
					sw->CountMotionless();
					this->fight_start = GetTickCount();
				}
				if (dynamic_cast<PlayScene*>(scene)) {
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					pScene->SpawnObject(weapon);
					isSpawnWeapon = true;
				}
				if (this->currentWeapon == EWeapon::STOPWATCH)
				{
					this->AddEnery(-5);
				}
				else
				{
					this->AddEnery(-1);
				}
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
	case SIMONSTATE::FIGHT_STAND:
		ani = SIMON_ANI_STAND_ATTACK;
		break;
	case SIMONSTATE::FIGHT_SIT:
		ani = SIMON_ANI_SIT_ATTACK;
		break;
	case SIMONSTATE::UP_STAIR_IDLE:
		ani = SIMON_ANI_IDLE_UPSTAIR;
		break;
	case SIMONSTATE::DOWN_STAIR_IDLE:
		ani = SIMON_ANI_IDLE_DOWNSTAIR;
		break;
	case SIMONSTATE::UP_STAIR_LEFT:
	case SIMONSTATE::UP_STAIR_RIGHT:
		ani = SIMON_ANI_STEP_UPSTAIR;
		break;
	case SIMONSTATE::DOWN_STAIR_LEFT:
	case SIMONSTATE::DOWN_STAIR_RIGHT:
		ani = SIMON_ANI_STEP_DOWNSTAIR;
		break;
	case SIMONSTATE::UP_STAIR_FIGHT:
		ani = SIMON_ANI_UPSTAIR_ATTACK;
		break;
	case SIMONSTATE::DOWN_STAIR_FIGHT:
		ani = SIMON_ANI_DOWNSTAIR_ATTACK;
		break;
	case SIMONSTATE::DEFLECT:
		ani = SIMON_ANI_DEFLECT;
		break;
	case SIMONSTATE::DIE:
		ani = SIMON_ANI_DIE;
		break;
	default:
		break;
	}

	if (this->fight_start != 0 && !this->spawnWeapon)
	{
		whip->Render();
	}
	//DebugOut(L"SIMON state=%d \n", (int)state);
	int alpha = 255;
	if (untouchable) alpha = 128;

	animations[ani]->Render(nx, x, y, alpha);

	//RenderBoundingBox();
}

void CSIMON::SetState(SIMONSTATE state)
{


	switch (state)
	{
	case SIMONSTATE::ENTERENTRANCE:
		this->ResetAttack();
		nx = DIRECTION::RIGHT;
		vx = SIMON_WALKING_SPEED / 2;
		break;
	case SIMONSTATE::WALKING_RIGHT:
		isTouchRetroGrade = false;
		vx = SIMON_WALKING_SPEED;
		nx = DIRECTION::RIGHT;
		break;
	case SIMONSTATE::WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;

		nx = DIRECTION::LEFT;
		break;
	case SIMONSTATE::JUMP:
		isOnGround = false;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMONSTATE::IDLE:
		vx = 0;
		break;
	case SIMONSTATE::DIE:
		this->vx = 0;
		this->vy = 0;
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
		whip->ColOneTime = true;
		vx = this->state == SIMONSTATE::IDLE || this->state == SIMONSTATE::WALKING_LEFT
			|| this->state == SIMONSTATE::WALKING_RIGHT ? 0 : vx;
		this->fight_start = GetTickCount();
		break;
	case SIMONSTATE::FIGHT_SIT:
		whip->ColOneTime = true;
		this->fight_start = GetTickCount();
		break;
	case SIMONSTATE::DOWN_STAIR_FIGHT:
		whip->ColOneTime = true;
		this->fight_start = GetTickCount();
		break;
	case SIMONSTATE::UP_STAIR_FIGHT:
		whip->ColOneTime = true;
		this->fight_start = GetTickCount();
		break;
	case SIMONSTATE::UP_STAIR_RIGHT: {
		vy = -SIMON_UPSTAIR_VELOCITY;
		vx = SIMON_UPSTAIR_VELOCITY;
		nx = DIRECTION::RIGHT;
		break;
	}
	case SIMONSTATE::DOWN_STAIR_RIGHT: {
		vy = SIMON_UPSTAIR_VELOCITY;
		vx = SIMON_UPSTAIR_VELOCITY;
		nx = DIRECTION::RIGHT;
		break;
	}
	case SIMONSTATE::UP_STAIR_LEFT: {
		nx = DIRECTION::LEFT;
		vy = -SIMON_UPSTAIR_VELOCITY;
		vx = -SIMON_UPSTAIR_VELOCITY;
		break;
	}
	case SIMONSTATE::DOWN_STAIR_LEFT: {
		DebugOut(L"State SIMON_STATE_DOWNSTAIR_LEFT \n");
		nx = DIRECTION::LEFT;
		vy = SIMON_UPSTAIR_VELOCITY;
		vx = -SIMON_UPSTAIR_VELOCITY;
		break;
	}
	case SIMONSTATE::DOWN_STAIR_IDLE:
	{
		DebugOut(L"State SIMONSTATE:DOWM_STAIR_IDLE \n");

		this->isOnStair = true;
		this->isFirstStepOnStair = true; // dung` khi set state mac dinh cua simon
		this->startOnStair = false; // cho phép nhấn tiếp
		if (nx == DIRECTION::RIGHT)
		{
			this->onStairDirection = STAIRDIRECTION::DOWNRIGHT;
		}
		else if (nx == DIRECTION::LEFT)
		{
			this->onStairDirection = STAIRDIRECTION::DOWNLEFT;
		}

		if (this->state != SIMONSTATE::DOWN_STAIR_FIGHT && this->state != SIMONSTATE::UP_STAIR_FIGHT) {
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
		}

		vx = 0;
		vy = 0;
		break;
	}
	case SIMONSTATE::UP_STAIR_IDLE: {

		this->isOnStair = true;
		this->isFirstStepOnStair = true; // dung` khi set state mac dinh cua simon
		this->startOnStair = false; // cho phép nhấn tiếp
		//tránh trường hợp khi simon attack y thay đổi làm floor
		// làm tròn xuống 1px
		if (nx == DIRECTION::RIGHT)
		{
			this->onStairDirection = STAIRDIRECTION::UPRIGHT;
		}
		else if (nx == DIRECTION::LEFT)
		{
			this->onStairDirection = STAIRDIRECTION::UPLEFT;
		}

		if (this->state != SIMONSTATE::DOWN_STAIR_FIGHT && this->state != SIMONSTATE::UP_STAIR_FIGHT) {
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
		}


		//DebugOut(L" LastStepOnStairPos x=%f y=%f", LastStepOnStairPos.x, LastStepOnStairPos.y);
		vx = 0;
		vy = 0;
		break;
	case SIMONSTATE::DEFLECT:
		vy = -SIMON_DEFLECT_SPEED_Y;
		if (nx == DIRECTION::LEFT)
		{
			vx = SIMON_DEFLECT_SPEED_X;
		}
		else
		{
			vx = -SIMON_DEFLECT_SPEED_X;
		}
		DebugOut(L"State SIMONSTATE:DEFLECT \n");
		this->ResetAttack();
		this->upgrade_start = GetTickCount();
		break;
	}

	}

	this->state = state;

}

void CSIMON::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 14;
	top = y;

	right = left + SIMON_BBOX_WIDTH;
	bottom = top + SIMON_BBOX_HEIGHT;

}

