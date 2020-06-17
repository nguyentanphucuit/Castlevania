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

	float velocity = ghost_fly_velocity;
	CGameObject::Update(dt, scene);
	if (dynamic_cast<PlayScene*>(scene)){

		if (!start_attack){

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

			if (gPos.x > simonPos.x){
				nx = DIRECTION::LEFT;
				int min = l - 60;
				int max = l;
				vx = -velocity;
				targer.x = rand() % (max + 1 - min) + min;
			}
			else{
				nx = DIRECTION::RIGHT;
				int min = r;
				int max = r + 60;
				targer.x = rand() % (max + 1 - min) + min;
				vx = velocity;
			}


			if (gPos.y > simonPos.y){
				int min = t;
				int max = t + 60;
				vy = -velocity;
				targer.x = rand() % (max + 1 - min) + min;
			}
			else{
				int min = b;
				int max = b + 60;
				targer.y = rand() % (max + 1 - min) + min;
				vy = velocity;
			}


			auto tx = abs(targer.x - gPos.x) / velocity;
			auto ty = abs(targer.y - gPos.y) / velocity;

			minTime = tx < ty ? tx : ty;

			auto sinValue = abs(targer.y - gPos.y) / sqrt(pow(abs(gPos.x - targer.x), 2) + pow(abs(targer.y - gPos.y), 2));
			if (sinValue > 1)
			{
				sinValue = 1;
			}
			// tính góc trả về đơn vị radian
			auto angle = asin(sinValue);
			// đổi ra độ
			this->angle = angle / PI * 180;
			start_attack = GetTickCount();

		}

		if (start_attack != 0){
			if (GetTickCount() - start_attack > minTime)
				this->start_attack = 0;
			else
			{
				x += dx * cos(this->angle * PI / 180);
				y += dy * sin(this->angle * PI / 180);
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

