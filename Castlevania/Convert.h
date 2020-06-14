#include <unordered_map>
#include <string>

///Object Layer
const enum ObjectID
{
	_Player,
	_Wall,
	_Ground,
	_HMoney,
	_Torch,
	_Nextmap,
	_Entrance,
	_NextScene,
	_IMoney,
	_Castle,
	_Camera,
	_Enemy,
	_Stair,
	_Birck,
	_Candle,
	_Door,
	_Boss,
	_BossBorder,
	_BossTrigger,
	_Water,
	_CheckRetrograde,
	_Platform
};

const auto string2EntityType = std::unordered_map<std::string, ObjectID>
{
	{ "Player", ObjectID::_Player },
	{ "Wall", ObjectID::_Wall },
	{ "Ground", ObjectID::_Ground },
	{ "HMoney", ObjectID::_HMoney,},
	{ "Camera", ObjectID::_Camera},
	{ "Torch", ObjectID::_Torch },
	{ "Nextmap", ObjectID::_Nextmap },
	{ "Entrance", ObjectID::_Entrance },
	{ "NextScene", ObjectID::_NextScene },
	{ "IMoney", ObjectID::_IMoney },
	{ "Castle", ObjectID::_Castle },
	{ "BossTrigger", ObjectID::_BossTrigger },
	{ "BossBorder", ObjectID::_BossBorder },
	{ "BOSS", ObjectID::_Boss },
	{ "Door", ObjectID::_Door },
	{ "Brick", ObjectID::_Birck },
	{ "Enemy", ObjectID::_Enemy },
	{ "Stair", ObjectID::_Stair },
	{ "Candle", ObjectID::_Candle },
	{ "Water", ObjectID::_Water },
	{ "CheckRetrograde", ObjectID::_CheckRetrograde},
	{ "Platform", ObjectID::_Platform}
};

