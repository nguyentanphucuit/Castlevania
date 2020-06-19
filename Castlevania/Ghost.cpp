#include "Ghost.h"
#include "Debug.h"
#include "Ground.h"
#include "Simon.h"


void Ghost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + GHOST_BBOX_WIDTH;
	bottom = top + GHOST_BBOX_HEIGHT;
}

void Ghost::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, scene);
	if (dynamic_cast<PlayScene*>(scene)) {

		if (!start_attack) {

			auto pScene = dynamic_cast<PlayScene*>(scene);
			float l, t, r, b;
			float ml, mt, mr, mb;
			this->GetBoundingBox(ml, mt, mr, mb);

			pScene->GetSimon()->GetBoundingBox(l, t, r, b);
			D3DXVECTOR2 simonPos;
			simonPos.x = l + (r - l) / 2;
			simonPos.y = t + (b - t) / 2;

			D3DXVECTOR2 gPos;
			gPos.x = ml + (mr - ml) / 2;
			gPos.y = mt + (mb - mt) / 2;

			if (gPos.x > simonPos.x) {
				nx = DIRECTION::LEFT;
				int min = l - GHOST_BBOX_WIDTH * 2;
				int max = l;
				vx = -GHOST_VELOCITY;
				targer.x = rand() % (max + 1 - min) + min;
			}
			else {
				nx = DIRECTION::RIGHT;
				int min = r;
				int max = r + GHOST_BBOX_WIDTH * 2;
				targer.x = rand() % (max + 1 - min) + min;
				vx = GHOST_VELOCITY;
			}


			if (gPos.y > simonPos.y) {
				int min = t;
				int max = t + GHOST_BBOX_HEIGHT * 2;
				vy = -GHOST_VELOCITY;
				targer.x = rand() % (max + 1 - min) + min;
			}
			else {
				int min = b;
				int max = b + GHOST_BBOX_HEIGHT * 2;
				targer.y = rand() % (max + 1 - min) + min;
				vy = GHOST_VELOCITY;
			}


			auto tx = abs(targer.x - gPos.x) / GHOST_VELOCITY;
			auto ty = abs(targer.y - gPos.y) / GHOST_VELOCITY;

			minTime = tx < ty ? tx : ty;

			auto sinValue = abs(targer.y - gPos.y) / sqrt(pow(abs(gPos.x - targer.x), 2) + pow(abs(targer.y - gPos.y), 2));
			if (sinValue > 1)
			{
				sinValue = 1;
			}

			auto angle = asin(sinValue);

			this->angle = angle;
			start_attack = GetTickCount();

		}

		if (start_attack != 0){
			if (GetTickCount() - start_attack > minTime)
				this->start_attack = 0;
			else
			{
				x += dx * cos(this->angle);
				y += dy * sin(this->angle);
			}

		}
	}
}

void Ghost::Render()
{

	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}


Ghost::Ghost() :Enemy()
{
	AddAnimation("GHOST_ANI_FLY");
}

