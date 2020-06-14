#include "Spawer.h"
#include"define.h"

void Spawner::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (dynamic_cast<PlayScene*>(scene))
	{
		auto pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam=pScene->GetCamera();

		float l, t, r, b;
		this->GetBoundingBox(l, t, r, b);


		if (this->enemyDef==CEnemy::BAT || this->enemyDef == CEnemy::BLACKKNIGHT)
		{
			
				if (this->AABB(l, t, r, b, cam.x, cam.y, cam.x + SCREENSIZE::WIDTH, cam.y + SCREENSIZE::HEIGHT) )
				{
					if (!this->isSpawned)
					{
						auto enemy = EnemyFactory::SpawnEnemy<Enemy*>(this->enemyDef);
						enemy->SetPosition(x, y);
						if (dynamic_cast<Bat*>(enemy))
						{
							auto bat = dynamic_cast<Bat*>(enemy);
							bat->SetOy();
						}
						else if (dynamic_cast<BlackKnight*>(enemy)) {
							auto blackKnight = dynamic_cast<BlackKnight*>(enemy);
							blackKnight->Area(this->startPos, this->endPos);
						}
						else if (dynamic_cast<Ghost*>(enemy)) {
							auto ghost = dynamic_cast<Ghost*>(enemy);
							ghost->Area(this->startPos, this->endPos);
						}
						else if (dynamic_cast<Ghost*>(enemy)) {
							auto ghost = dynamic_cast<Ghost*>(enemy);
							ghost->Area(this->startPos, this->endPos);
						}
						pScene->SpawnObject(enemy);
						this->isSpawned = true;

					}
				
				}
				else
				{
					this->isSpawned = false;
				}
		}
		else if (this->enemyDef == CEnemy::GHOST || this->enemyDef == CEnemy::HUNCHBACK) {

			if (this->AABB(l, t, r, b, cam.x, cam.y, cam.x + SCREENSIZE::WIDTH, cam.y + SCREENSIZE::HEIGHT))
			{
				if (!this->isSpawned)
				{
					auto enemy = EnemyFactory::SpawnEnemy<Enemy*>(this->enemyDef);
					enemy->SetPosition(x, y);
					if (dynamic_cast<Bat*>(enemy))
					{
						auto bat = dynamic_cast<Bat*>(enemy);
						bat->SetOy();
					}
					else if (dynamic_cast<BlackKnight*>(enemy)) {
						auto blackKnight = dynamic_cast<BlackKnight*>(enemy);
						blackKnight->Area(this->startPos, this->endPos);
					}
					else if (dynamic_cast<Ghost*>(enemy)) {
						auto ghost = dynamic_cast<Ghost*>(enemy);
						ghost->Area(this->startPos, this->endPos);
					}
					else if (dynamic_cast<Hunchback*>(enemy)) {
						auto hunchback = dynamic_cast<Hunchback*>(enemy);
						hunchback->Area(this->startPos, this->endPos);
					}
					pScene->SpawnObject(enemy);
					this->isSpawned = true;

				}

			}
			else
			{
				this->isSpawned = false;
			}
		}
			
	}
}



