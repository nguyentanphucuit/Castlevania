#pragma once
#include "Effect.h"
#include "Flame.h"
#include"DebrisBrick.h"

enum class CEffect {
	FLAME,
	DEBRIS,
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
	case CEffect::DEBRIS:
		return new DebrisBrick();
		break;
	default:
		break;
	}
	return T();
}
