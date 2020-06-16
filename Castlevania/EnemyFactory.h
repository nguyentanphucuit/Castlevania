#pragma once
#include "Enemy.h"
#include "Bat.h"
#include "BlackKnight.h"
#include "Ghost.h"
#include "Hunchback.h"
#include "White.h"
#include "Raven.h"
#include "Zombie.h"

enum class CEnemy {
	BAT = 0,
	BLACKKNIGHT,
	GHOST,
	HUNCHBACK,
	WHITE,
	RAVEN,
	ZOMBIE
};
class EnemyFactory
{
public:
	template <typename T> static T SpawnEnemy(CEnemy cEnemy);
};

template<typename T>
inline T EnemyFactory::SpawnEnemy(CEnemy cEnemy)
{
	
	switch (cEnemy) {
	case CEnemy::BAT:
		return new Bat();
		break;
	case CEnemy::BLACKKNIGHT:
		return new BlackKnight();
		break;
	case CEnemy::GHOST:
		return new Ghost();
		break;
	case CEnemy::HUNCHBACK:
		return new Hunchback();
		break;
	case CEnemy::WHITE:
		return new White();
		break;
	case CEnemy::RAVEN:
		return new Raven();
		break;
	case CEnemy::ZOMBIE:
		return new Zombie();
		break;
	}
	return T();
}
