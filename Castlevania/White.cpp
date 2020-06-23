#include "White.h"
#include "Debug.h"
#include "Ground.h"
#include "Simon.h"
#include "WeaponFactory.h"
#include "EnemyFactory.h"


void White::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 2;
	right = left + WHITE_BBOX_WIDTH;
	bottom = top + WHITE_BBOX_HEIGHT - 2;
}

void White::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, scene);
	if (this->isMotionless)
	{
		return;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	vy += WHITE_GRAVITY * dt;

	auto enemy = EnemyFactory::SpawnEnemy<Enemy*>(CEnemy::BONE);

	if (vx < 0) nx = DIRECTION::LEFT;
	else nx = DIRECTION::RIGHT;


	if (numWeapon  < 3 && GetTickCount() - timeSpawn > TIME_WAIT) {
		timeSpawn = GetTickCount();
		enemy->SetPosition(this->x, this->y + NEARLY_WEAPON);
		enemy->SetNx(this->nx);
		if (dynamic_cast<PlayScene*>(scene)) {
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			pScene->SpawnObject(enemy);
		}
		numWeapon++;
	}
	if (numWeapon == 3) {
		if (loadTimeSpawn ==0)
		{
			loadTimeSpawn = GetTickCount();
		}
		
	}
	if (loadTimeSpawn!=0 && GetTickCount()-loadTimeSpawn> TIME_WAIT_BONE)
	{
		loadTimeSpawn = 0;
		numWeapon = 0;

	}

	
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (ny <= 0)
			y += min_ty * dy + ny * 0.4f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				
				int jumpRank = rand()%(2-1+1)+1;
				if (jumpRank==1)
				{
					vy = 0;
				}
				else
				{
					float minvy = -0.40;
					float maxvy = -0.65;
					vy = minvy + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxvy - minvy)));
				}
				float minvx = -0.40;
				float maxvx = 0.40;
				vx = minvx + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxvx - minvx)));
			}
			else {
				if (e->nx != 0)
					x += dx;
				else if (e->ny < 0) {
					y += dy;
				}

			}
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void White::Render()
{

	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void White::Area(int startPos, int endPos)
{
	this->_endPos = endPos;
	this->_startPos = startPos;
}

White::White() :Enemy()
{
	AddAnimation("WHITE_ANI_JUMP");
	this->isMotionless = false;
}

