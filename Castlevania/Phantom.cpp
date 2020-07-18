#include "Phantom.h"



void Phantom::FlyTo(D3DXVECTOR2 target, float velocity)
{

	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);
	D3DXVECTOR2 boss_center;
	boss_center.x = l + (r - l) / 2;
	boss_center.y = t + (b - t) / 2;
	if (boss_center.x > target.x)
		vx = -velocity;
	else 
		vx = velocity;
	if (boss_center.y > target.y)
		vy = -velocity;
	else
		vy = velocity;



	auto tx = abs(boss_center.x - target.x) / velocity;
	auto ty = abs(boss_center.y - target.y) / velocity;
	maxTime = tx > ty ? tx : ty;
	auto sinValue = abs(target.y - boss_center.y) / sqrt(pow(abs(boss_center.x - target.x), 2) + pow(abs(boss_center.y - target.y), 2));
	if (sinValue > 1)
	{
		sinValue = 1;
	}
	auto angle = asin(sinValue);
	this->angle = angle;
}

void Phantom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + PHANTOM_BBOX_WIDTH;
	bottom = top + PHANTOM_BBOX_HEIGHT;
}

void Phantom::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, scene);
	Hud::SetBossHp(this->hp);
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		if (pScene->GetSimon()->x - this->x > 40) {
			this->SetState(PHANTOMSTATE::FLY);
		}
		D3DXVECTOR2 cam = pScene->GetCamera();
		box_attive.left = cam.x;
		box_attive.top = cam.y;
		box_attive.right = cam.x + SCREENSIZE::WIDTH - 80;
		box_attive.bottom = cam.y + SCREENSIZE::HEIGHT - 220;
	}

	if (this->state == PHANTOMSTATE::FLY) {
		float l, t, r, b;
		this->GetBoundingBox(l, t, r, b);

		D3DXVECTOR2 boss_center;
		boss_center.x = l + (r - l) / 2;
		boss_center.y = t + (b - t) / 2;
		D3DXVECTOR2 simon_center = { 0,0 };
		float ml = 0, mt = 0, mr = 0, mb = 0;
		if (dynamic_cast<PlayScene*>(scene)) {

			auto pScene = dynamic_cast<PlayScene*>(scene);
			pScene->GetSimon()->GetBoundingBox(ml, mt, mr, mb);
			simon_center.x = ml + (mr - ml) / 2;
			simon_center.y = mt + (mb - mt) / 2;

		}

		this->box_slow_attack.left = boss_center.x - 100;
		this->box_slow_attack.top = boss_center.y - 100;
		this->box_slow_attack.right = boss_center.x + 100;
		this->box_slow_attack.bottom = boss_center.y + 100;

		this->box_fast_attack.left = boss_center.x - 200;
		this->box_fast_attack.top = boss_center.y - 300;
		this->box_fast_attack.right = boss_center.x + 200;
		this->box_fast_attack.bottom = boss_center.y + 300;

		if (fly_ramdom_start == 0 && waiting_start == 0) {
			if (CGameObject::AABB(ml, mt, mr, mb, this->box_slow_attack.left,
				this->box_slow_attack.top,
				this->box_slow_attack.right,
				this->box_slow_attack.bottom)) {
				if (start_attack == 0) {
					start_attack = GetTickCount();
					target.x = simon_center.x;
					target.y = simon_center.y;
					FlyTo(target, FLY_SLOW);
				}
			}
			else if (CGameObject::AABB(ml, mt, mr, mb, this->box_fast_attack.left,
				this->box_fast_attack.top,
				this->box_fast_attack.right,
				this->box_fast_attack.bottom)) {
				if (start_attack == 0) {
					start_attack = GetTickCount();
					target.x = simon_center.x;
					target.y = simon_center.y;
					FlyTo(target, FLY_FAST);
				}
			}
			else {
				target.x = rand() % (box_attive.right - box_attive.left + 1) + box_attive.left;
				target.y = rand() % (box_attive.bottom - box_attive.top + 1) + box_attive.top;
				FlyTo(target, FLY_SLOW);
				if (fly_ramdom_start == 0) {
					fly_ramdom_start = GetTickCount();
				}
			}
		}
		if (start_attack != 0) {
			if (maxTime != 0 && GetTickCount() - start_attack > maxTime) {
				start_attack = 0;
				fly_ramdom_start = GetTickCount();
				target.x = rand() % (box_attive.right - box_attive.left + 1) + box_attive.left;
				target.y = rand() % (box_attive.bottom - box_attive.top + 1) + box_attive.top;
				FlyTo(target, FLY_SLOW);
			}
		}
		if (fly_ramdom_start != 0 && maxTime != 0 && GetTickCount() - fly_ramdom_start > maxTime) {
			int rank = rand() % (2 - 1 + 1) + 1;
			if (rank == 1) {
				fly_ramdom_start = 0;
				waiting_start = GetTickCount();
				vx = 0;
				vy = 0;
			}
			else {
				target.x = rand() % (box_attive.right - box_attive.left + 1) + box_attive.left;
				target.y = rand() % (box_attive.bottom - box_attive.top + 1) + box_attive.top;
				FlyTo(target, FLY_SLOW);
				fly_ramdom_start = GetTickCount();
			}
		}
		if (waiting_start != 0 && GetTickCount() - waiting_start > WAIT_TIME) {
			start_attack = 0;
			waiting_start = 0;
			fly_ramdom_start = 0;
		}
		if (start_attack != 0 || fly_ramdom_start != 0) {
			x += dx * cos(angle);
			y += dy * sin(angle);
		}
	}
}

void Phantom::Render()
{
	//RenderBoundingBox();
	int ani = 0;
	switch (this->state)
	{
	case PHANTOMSTATE::IDLE:
		ani = PHANTOM_ANI_IDLE;
		animations[ani]->Render(nx, x, y);
		break;
	case PHANTOMSTATE::FLY:
		ani = PHANTOM_ANI_FLY;
		animations[ani]->Render(nx, x, y);
		break;
	default:
		break;
	};

}


void Phantom::SetState(PHANTOMSTATE state)
{
	switch (state) {
	case PHANTOMSTATE::IDLE:
		vx = 0;
		vy = 0;
		break;
	case PHANTOMSTATE::FLY:

		break;
	}
	this->state = state;
}

Phantom::Phantom() :Enemy()
{
	AddAnimation("PHANTOM_ANI_IDLE");
	AddAnimation("PHANTOM_ANI_FLY");
	this->hp = 16;
	this->isMotionless = false;
}
