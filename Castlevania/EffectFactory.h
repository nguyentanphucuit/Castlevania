#pragma once
#include "Effect.h"
#include "Flame.h"

enum class CEffect {
	FLAME,
};
class EffectFactory
{
public:
	template <typename T> static T SpawnEffect(CEffect ceffect);
};

template<typename T>
inline T EffectFactory::SpawnEffect(CEffect ceffect)
{
	switch (ceffect) {
	case CEffect::FLAME:
		return new Flame();
		break;
	default:
		break;
	}
	return T();
}
