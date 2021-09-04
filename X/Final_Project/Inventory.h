#pragma once
#include "InventoryItem.h"
#include "Food.h"
#include "Resource.h"
#include "CraftPanel.h"


class Inventory
{

private:

	std::vector<InventoryItem> myItems;
	X::Math::Vector2 mScreenPosition;
	X::Math::Vector2 mSelectPosition;
	X::TextureId mTextureID = 0;
	X::TextureId mTextureIDSelect = 0;

	const X::Math::Vector2& ReturnPositionToRenderItem(size_t index);

public:

	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static Inventory& Get();

	//functions

	bool AddItemsFood(FoodType type);
	bool AddItemsResource(ResourceType type);


	void Load();
	void Render();
	void Update();
	void Unload();

};

