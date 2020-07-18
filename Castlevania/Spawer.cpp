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

		if (this->enemyDef == CEnemy::HUNCHBACK
			|| this->enemyDef == CEnemy::WHITE
			|| this->enemyDef == CEnemy::RAVEN
			|| this->enemyDef == CEnemy::BLACKKNIGHT
			|| this->enemyDef == CEnemy::BAT) {

			if (this->AABB(l, t, r, b, cam.x, cam.y, cam.x + SCREENSIZE::WIDTH, cam.y + SCREENSIZE::HEIGHT)){	
				if (!this->isSpawned){
					auto enemy = EnemyFactory::SpawnEnemy<Enemy*>(this->enemyDef);
					enemy->SetPosition(x, y);
					if (dynamic_cast<Hunchback*>(enemy)) {
						if (numHunchback >= num)
							return;
						auto hunchback = dynamic_cast<Hunchback*>(enemy);
						numHunchback++;
					}
					else if (dynamic_cast<White*>(enemy))  {
						if (numWhite >= num)
							return;
						auto Bone = dynamic_cast<White*>(enemy);
						numWhite++;
					}
					else if (dynamic_cast<Raven*>(enemy)) {
						if (numRaven >= num)
							return;
						auto raven = dynamic_cast<Raven*>(enemy);
						numRaven++;
						raven->Area(this->startPos, this->endPos);
					}				
					else if (dynamic_cast<BlackKnight*>(enemy)) {
						if (numBlackKnight >= num)
							return;
						auto blackKnight = dynamic_cast<BlackKnight*>(enemy);
						numBlackKnight++;
						blackKnight->Area(this->startPos, this->endPos);
					}
					else if (dynamic_cast<Bat*>(enemy)){
						if (numBat >= num)
							return;
						auto bat = dynamic_cast<Bat*>(enemy);
						numBat++;
						bat->SetOy();
					}
					pScene->enemies.push_back(enemy);
					enemy->spawnOwner = this;
					pScene->SpawnObject(enemy);
					this->isSpawned = true;
				}
			}
			else
				this->isSpawned = false;
		}
		else if (this->enemyDef == CEnemy::GHOST) {
			if (this->AABB(l, t, r, b, cam.x, cam.y, cam.x + SCREENSIZE::WIDTH, cam.y + SCREENSIZE::HEIGHT)){
				if (!this->isSpawned && l* nxE < nxE *pScene->GetSimon()->x - GHOST_BBOX_WIDTH * 3){
					auto enemy = EnemyFactory::SpawnEnemy<Enemy*>(this->enemyDef);
					enemy->SetPosition(x, y);
					if (dynamic_cast<Ghost*>(enemy)) {
						if (numGhost >= num)
							return;
						auto ghost = dynamic_cast<Ghost*>(enemy);
						numGhost++;
					}
					
					pScene->enemies.push_back(enemy);
					enemy->spawnOwner = this;
					pScene->SpawnObject(enemy);
					this->isSpawned = true;
				}
			}
			else
				this->isSpawned = false;
		}
		else if (this->enemyDef == CEnemy::ZOMBIE) {
			if (this->AABB(l, t, r, b, cam.x, cam.y, cam.x + SCREENSIZE::WIDTH, cam.y + SCREENSIZE::HEIGHT)) {
				
				if (!this->isSpawned && GetTickCount()-zombieTime > TIME_SPAWN_ZOMBIE
					&& l * nxE < nxE * pScene->GetSimon()->x - ZOMBIE_BBOX_WIDTH * 3) {
					auto enemy = EnemyFactory::SpawnEnemy<Enemy*>(this->enemyDef);
					enemy->SetPosition(x, y);
					int numRand = rand() % (num + 1 - 0) + 0;
					if (dynamic_cast<Zombie*>(enemy)) {
						if (numZombie >= num)
							return;
						auto zombie = dynamic_cast<Zombie*>(enemy);
						numZombie++;
						zombie->Nx(nxE);
					}
					pScene->enemies.push_back(enemy);
					enemy->spawnOwner = this;
					pScene->SpawnObject(enemy);

					zombieTime = GetTickCount();
					numSpawn++;
					
					if (numSpawn > numRand)
						this->isSpawned = true;
				}
			}
			else {
				this->isSpawned = false;
				numSpawn = 0;
			}
				
		}
			
	}
}



