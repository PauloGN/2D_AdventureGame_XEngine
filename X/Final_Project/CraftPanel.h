#pragma once
#include<XEngine.h>
#include "Resource.h"
#include "InventoryItem.h"

class CraftPanel
{

private:

	std::vector<InventoryItem> myItems;
	X::Math::Vector2 mScreenPosition;
	X::TextureId mTextureID = 0;
	

	std::vector<X::TextureId> mCraftableItems;

	const X::Math::Vector2& ReturnPositionToRenderItem(size_t index);

	bool mutable isCraftReady;

	ToolType mutable tooltype;

public:

	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static CraftPanel& Get();

	//functions

	bool AddItemsResource(ResourceType type);
	const X::TextureId& ItemToCraftTexture() const;
		

	void Load();
	void Render();
	void Update();
	void Unload();

};

