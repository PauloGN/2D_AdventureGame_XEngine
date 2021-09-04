#pragma once
#include "Food.h"
#include "Resource.h"


class InventoryItem
{
public:

	bool isFood;

	std::shared_ptr<Food> mItemF;
	std::shared_ptr<Resource> mItemR;
	int mQuantityOfItems = 1;
	
	bool AddOne(bool bIsFood);

};

