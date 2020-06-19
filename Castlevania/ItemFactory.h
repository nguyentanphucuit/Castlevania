﻿#pragma once
#include "Item.h"
#include "Heart.h"
#include "BHeart.h"
#include "IDagger.h"
#include "IWhip.h"
#include "IMoney.h"
#include "IAXE.h"
#include "IFireBomb.h"
#include "IBoomerang.h"
#include "IInvisible.h"

// declarate Item
enum class EItem
{
	BIGHEART=1,
	WHIP,
	DAGGER,
	HEART,
    MONEY,
    AXE,
    FIREBOMB,
    BOOMERANG,
    INVISIBLE

};

class ItemFactory
{

public:

	template <typename T> static T SpawnItem(EItem item);

};

template<typename T>
inline T ItemFactory::SpawnItem(EItem eitem)
{
   
    switch (eitem)
    {
    case EItem::BIGHEART: 
        return new BHeart();
        break;
    case EItem::WHIP:
        return new IWhip();
        break;
    case EItem::DAGGER:
        return new IDagger();
        break;
    case EItem::HEART:
        return new CHeart();
        break;
    case EItem::MONEY:
        return new IMoney();
        break;
    case EItem::AXE:
        return new IAXE();
        break;
    case EItem::FIREBOMB:
        return new IFireBomb();
        break;
    case EItem::BOOMERANG:
        return new IBoomerang();
        break;
    case EItem::INVISIBLE:
        return new IInvisible();
    default:
        break;
    }

    return T();
}
