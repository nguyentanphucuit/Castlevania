#pragma once
#include "Enemy.h"
#include "Bat.h"
#include "BlackKnight.h"

enum class CEnemy {
	BAT = 0,
	BLACKKNIGHT,
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
	}
	return T();
}
