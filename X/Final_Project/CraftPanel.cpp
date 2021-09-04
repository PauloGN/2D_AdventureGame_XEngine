#include "CraftPanel.h"
#include "Inventory.h"

namespace
{

	std::unique_ptr<CraftPanel> CraftInstance = nullptr;

}


void CraftPanel::StaticInitialize()
{

	XASSERT(CraftInstance == nullptr, "Erro.. CraftInstance has already an instance");
	CraftInstance = std::make_unique<CraftPanel>();

}

void CraftPanel::StaticTerminate()
{
	CraftInstance.reset();
}

CraftPanel& CraftPanel::Get()
{
	XASSERT(CraftInstance != nullptr, "Erro.. CraftInstance has already an instance");
	return*CraftInstance;
}

//======================================================================\\

const X::Math::Vector2& CraftPanel::ReturnPositionToRenderItem(size_t index)
{

	X::Math::Vector2 position;
	switch (index)
	{
    case 0:

        position = {1010,620};

        break;
    case 1:
        position = { 1080,620 };
        break;

	default:
        
		break;
	}

	return position;
}
bool CraftPanel::AddItemsResource(ResourceType type)
{


    for (auto it = myItems.begin(); it != myItems.end(); it++)
    {
        if (it->mItemR.get() == nullptr)
            continue;

        if (it->mItemR.get()->mResourceType == type)
        {
            return it->AddOne(false);
        }

    }

    //limit of objects inside the craft system = 2
    if (myItems.size() == 2)
    {
        return false;
    }

    InventoryItem resource;
    resource.mItemR = std::make_shared<Resource>(900, 250, type);
    resource.mItemR.get()->Load();

    myItems.push_back(resource);

    return true;
}

const X::TextureId& CraftPanel::ItemToCraftTexture() const
{
    
    if (myItems.size() >= 2)
    {

        if (myItems[0].mQuantityOfItems < 4 &&
            myItems[1].mQuantityOfItems < 4)
        {
            
            if ((myItems[0].mItemR->mResourceType == ResourceType::spearHead &&
                myItems[1].mItemR->mResourceType == ResourceType::spearShaft) || (
                    myItems[1].mItemR->mResourceType == ResourceType::spearHead &&
                    myItems[0].mItemR->mResourceType == ResourceType::spearShaft))
            {
                isCraftReady = true;
                tooltype = ToolType::spear;
                return mCraftableItems[2];
            }

        }


        if (myItems[0].mQuantityOfItems == 4 &&
            myItems[1].mQuantityOfItems == 4)
        {
            isCraftReady = true;
            // 4 sticks and 4 hard Rocks = fire and vice versa
            if ((myItems[0].mItemR->mResourceType == ResourceType::hardRock &&
                    myItems[1].mItemR->mResourceType == ResourceType::w_Sticks)||(
                    myItems[1].mItemR->mResourceType == ResourceType::hardRock &&
                    myItems[0].mItemR->mResourceType == ResourceType::w_Sticks))
            {
                tooltype = ToolType::fire;
                return mCraftableItems[0];
            }
            // 4 sticks and 4 woods = fire and vice versa
            else if ((myItems[0].mItemR->mResourceType == ResourceType::wood &&
                         myItems[1].mItemR->mResourceType == ResourceType::w_Sticks)||(
                         myItems[1].mItemR->mResourceType == ResourceType::wood &&
                         myItems[0].mItemR->mResourceType == ResourceType::w_Sticks))
            {
                tooltype = ToolType::fire;
                return mCraftableItems[0];
            }
            // 4 hardRocks and 4 woods = RockHamer and vice versa
            else if ((myItems[0].mItemR->mResourceType == ResourceType::wood &&
                         myItems[1].mItemR->mResourceType == ResourceType::hardRock)||(
                         myItems[1].mItemR->mResourceType == ResourceType::wood &&
                         myItems[0].mItemR->mResourceType == ResourceType::hardRock))
            {
                tooltype = ToolType::rockHammer;
                return mCraftableItems[1];
            }
            // 4 chippedStone and 4 woods = StoneAx and vice versa
            else if ((myItems[0].mItemR->mResourceType == ResourceType::wood &&
                     myItems[1].mItemR->mResourceType == ResourceType::chippedStone) || (
                     myItems[1].mItemR->mResourceType == ResourceType::wood &&
                     myItems[0].mItemR->mResourceType == ResourceType::chippedStone))
            {
                tooltype = ToolType::stoneAx;
                return mCraftableItems[3];
            }
            // 4 chippedStone and 4 hardRocks = spearHead and vice versa
            else if ((myItems[0].mItemR->mResourceType == ResourceType::hardRock &&
                     myItems[1].mItemR->mResourceType == ResourceType::chippedStone) || (
                     myItems[1].mItemR->mResourceType == ResourceType::hardRock &&
                     myItems[0].mItemR->mResourceType == ResourceType::chippedStone))
            {
                tooltype = ToolType::spearHead;
                return mCraftableItems[4];
            }
            else if ((myItems[0].mItemR->mResourceType == ResourceType::w_Sticks &&
                      myItems[1].mItemR->mResourceType == ResourceType::chippedStone) || (
                      myItems[1].mItemR->mResourceType == ResourceType::w_Sticks &&
                      myItems[0].mItemR->mResourceType == ResourceType::chippedStone))
            {
                tooltype = ToolType::spearShaft;
                return mCraftableItems[5];
            }
            else if ((myItems[0].mItemR->mResourceType == ResourceType::spearHead &&
                      myItems[1].mItemR->mResourceType == ResourceType::spearShaft) || (
                      myItems[1].mItemR->mResourceType == ResourceType::spearHead &&
                      myItems[0].mItemR->mResourceType == ResourceType::spearShaft))
            {
                tooltype = ToolType::spear;
                return mCraftableItems[2];
            }
            else
            {
                tooltype = ToolType::fire;
                return mCraftableItems[0];

            }
        }
    }
   return X::TextureId{};

}

void CraftPanel::Load()
{
	//CraftPanel texture and screen position
	mTextureID = X::LoadTexture("CraftPainel.png");
	mScreenPosition = { 1090,610 };

    //Load imagens of itens to craft

    mCraftableItems.push_back(X::LoadTexture("Fire.png")); // 0
    mCraftableItems.push_back(X::LoadTexture("RockHammer.png")); // 1
    mCraftableItems.push_back(X::LoadTexture("spear.png")); // 2
    mCraftableItems.push_back(X::LoadTexture("Axstone.png")); //3
    mCraftableItems.push_back(X::LoadTexture("spearHead.png")); //4
    mCraftableItems.push_back(X::LoadTexture("spearShaft.png")); //5

    // load variables
    isCraftReady = false;
    tooltype = ToolType::none;
}

void CraftPanel::Render()
{
    //Render Inventory visual representations
    X::DrawSprite(mTextureID, mScreenPosition);
  
    //Render Iten to craft
   
    const X::TextureId craftTexture = ItemToCraftTexture();
    
    if (isCraftReady)
    {
        X::DrawSprite(craftTexture, { 1160.0f, 620.0f });
        X::DrawScreenText("Press SPACE to create the item", 970, 690, 14, X::Colors::White);

    }

    //render inventory Items
    for (std::vector<InventoryItem>::iterator it = myItems.begin(); it != myItems.end(); it++)
    {

        if (it->mItemR.get() != nullptr)
        {
            const std::string info(std::to_string(it->mQuantityOfItems));
            it->mItemR.get()->RenderOnInventory(info.c_str());
        }

    }

}

void CraftPanel::Update()
{

    for (size_t i = 0; i < myItems.size(); i++)
    {

        if (myItems[i].mItemR.get() != nullptr)
        {
            myItems[i].mItemR.get()->SetPosition(ReturnPositionToRenderItem(i));
        }

    }

    if (isCraftReady)
    {
        if (X::IsKeyPressed(X::Keys::SPACE))
        {

            if (tooltype == ToolType::spearHead)
            {
                Inventory::Get().AddItemsResource(ResourceType::spearHead);
            }
            else if (tooltype == ToolType::spearShaft)
            {
                Inventory::Get().AddItemsResource(ResourceType::spearShaft);
            }
            else
            {
              Character::Get().AddTool(tooltype, ItemToCraftTexture());
            }


            myItems.clear();
            tooltype = ToolType::none;
            isCraftReady = false;
        }
    }
    else
    {
        //Clean Craft Panel
        if (X::IsKeyPressed(X::Keys::E))
        {
            myItems.clear();
        }
    }



}

void CraftPanel::Unload()
{

	myItems.clear();

}
