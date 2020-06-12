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



