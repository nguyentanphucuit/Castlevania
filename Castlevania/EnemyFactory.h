#pragma once
#include "Enemy.h"
#include "Bat.h"
#include "BlackKnight.h"
#include "Ghost.h"
#include "Hunchback.h"
#include "White.h"
#include "Raven.h"
#include "Zombie.h"
#include "Phantom.h"

enum class CEnemy {
	BAT = 0,
	BLACKKNIGHT,
	GHOST,
	HUNCHBACK,
	WHITE,
	RAVEN,
	ZOMBIE,
	PHANTOM
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
	case CEnemy::BLACKKNIGHT:
		return new BlackKnight();
	case CEnemy::GHOST:
		return new Ghost();
	case CEnemy::HUNCHBACK:
		return new Hunchback();
	case CEnemy::WHITE:
		return new White();
	case CEnemy::RAVEN:
		return new Raven();
	case CEnemy::ZOMBIE:
		return new Zombie();
	case CEnemy::PHANTOM:
		return new Phantom();
	}
	return T();
}
