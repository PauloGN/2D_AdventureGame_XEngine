#include "InventoryItem.h"

bool InventoryItem::AddOne(bool bIsFood)
{

	isFood = bIsFood;

	if (isFood)
	{
		if (mItemF.get()->mMax == mQuantityOfItems)
		{
			return false;
		}
		
	}else
	{
		if (mItemR.get()->mMax == mQuantityOfItems)
		{
			return false;
		}

	}

	mQuantityOfItems++;
	return true;
}
