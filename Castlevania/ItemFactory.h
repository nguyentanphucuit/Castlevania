#pragma once
#include "Item.h"
#include "Heart.h"
#include "BHeart.h"
#include "IDagger.h"
#include "IWhip.h"
// khai báo các loại item tại đây
enum class EItem
{
	BIGHEART=1,
	WHIP,
	DAGGER,
	HEART,

};

class ItemFactory
{

public:
	// Kiểu T trả về nhiều kiểu đối tượng khác nhau
	//đọc thêm về template
	template <typename T> static T SpawnItem(EItem item);

};

template<typename T>
inline T ItemFactory::SpawnItem(EItem eitem)
{
    Item* item = NULL;
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
    default:
        break;
    }

    return T();
}
