#include "Inventory.h"
#include <sstream>


namespace {


    std::unique_ptr<Inventory> inventoryInstance = nullptr;

}



void Inventory::StaticInitialize()
{
    XASSERT(inventoryInstance == nullptr, "Erro.. InventoryInstance has already an instance");
    inventoryInstance = std::make_unique<Inventory>();

}

void Inventory::StaticTerminate()
{

    inventoryInstance.reset();

}

Inventory& Inventory::Get()
{  
    XASSERT(inventoryInstance != nullptr, "Erro.. InventoryInstance has already an instance");
    return* inventoryInstance;
}


//==============================================================================================================================


bool Inventory::AddItemsFood(FoodType type)
{

    
    for (auto it = myItems.begin(); it != myItems.end(); it++)
    {
        if (it->mItemF.get() == nullptr)
            continue;

        

        if (it->mItemF.get()->mFoodtype == type)
        {          
             return it->AddOne(true);       
        }

    }
   
    InventoryItem food;
    food.mItemF = std::make_shared<Food>(1000,250,type);
    food.mItemF.get()->Load();
    food.isFood = true;
    myItems.push_back(food);
    
    return true;
}

bool Inventory::AddItemsResource(ResourceType type)
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

    InventoryItem resource;
    resource.mItemR = std::make_shared<Resource>(900, 250, type);
    resource.mItemR.get()->Load();

    myItems.push_back(resource);

    return true;
}

const X::Math::Vector2& Inventory::ReturnPositionToRenderItem(size_t index)
{

    X::Math::Vector2 screenPosition2Render;

    switch (index)
    {
    case 0:
        screenPosition2Render = { 950,100 };
        break;
    case 1:
        screenPosition2Render = { 1020,100 };
        break;
    case 2:
        screenPosition2Render = { 1090,100 };
        break;
    case 3:
        screenPosition2Render = { 1160,100 };
        break;
    case 4:
        screenPosition2Render = { 1230,100 };
        break;
    case 5:
        screenPosition2Render = { 950,160 };
        break;
    case 6:
        screenPosition2Render = { 1020,160 };
        break;
    case 7:
        screenPosition2Render = { 1090,160 };
        break;
    case 8:
        screenPosition2Render = { 1160,160 };
        break;
    case 9:
        screenPosition2Render = { 1230,160 };
        break;
    case 10:
        screenPosition2Render = { 950,220 };
        break;

    default:

        screenPosition2Render = { 900,300 };

        break;
    }


    return screenPosition2Render;
}

void Inventory::Load()
{
    //Inventory texture and screen position
    mTextureID = X::LoadTexture("InventoryS.png");
    mTextureIDSelect = X::LoadTexture("Select.png");
    mScreenPosition = {1090,270};
    mSelectPosition = {0,0};

}

void Inventory::Render()
{
  
    //Reder Inventory visual representations
    X::DrawSprite(mTextureID, mScreenPosition);
    X::DrawSprite(mTextureIDSelect, mSelectPosition);

    
    //render inventory Items
    for (std::vector<InventoryItem>::iterator it = myItems.begin(); it != myItems.end(); it++)
    {

        
        if (it->mItemF.get()!= nullptr)
        {
           
            const std::string info( std::to_string(it->mQuantityOfItems));          
            it->mItemF.get()->RenderOnInventory(info.c_str());
            
        }
        

        if (it->mItemR.get() != nullptr)
        {
            const std::string info(std::to_string(it->mQuantityOfItems));
            it->mItemR.get()->RenderOnInventory(info.c_str());
        }


    }


}

void Inventory::Update()
{

    for (size_t i = 0; i < myItems.size();i++)
    {

        if (myItems[i].mItemF.get() != nullptr)
        {
            myItems[i].mItemF.get()->SetPosition(ReturnPositionToRenderItem(i));          
        }


        if (myItems[i].mItemR.get() != nullptr)
        {
            myItems[i].mItemR.get()->SetPosition(ReturnPositionToRenderItem(i));           
        }

    }

    static size_t itemIndex = 0;
    if (X::IsKeyPressed(X::Keys::RIGHT))
    {
        itemIndex++;    
    }
    else if (X::IsKeyPressed(X::Keys::LEFT))
    {
        itemIndex--;
    }
    else if (X::IsKeyPressed(X::Keys::UP))
    {
        itemIndex -= 5;
    }
    else if (X::IsKeyPressed(X::Keys::DOWN))
    {
        itemIndex += 5;
    }

    if (itemIndex < 0)
    {
        itemIndex = 0;

    }else if (itemIndex > 10)
    {
        itemIndex = 0;
    }
    mSelectPosition = ReturnPositionToRenderItem(itemIndex);
    mSelectPosition.x += 1;

    if (X::IsKeyPressed(X::Keys::ENTER) && itemIndex <myItems.size())
    {

        if (myItems[itemIndex].isFood)
        {
            myItems[itemIndex].mQuantityOfItems--;
            //Actions to restore character vitality
            Character::Get().RestoreVitality(myItems[itemIndex].mItemF.get()->ReturnHealthRestore());
            
            if (myItems[itemIndex].mQuantityOfItems < 1)
            {
                myItems.erase(myItems.begin()+itemIndex);
            }

        }
        else//add itens into the craft system
        {

            if (Character::Get().isCraftPanelOpen)
            {
                //limit of objects inside the craft system = 2
                if (CraftPanel::Get().AddItemsResource(myItems[itemIndex].mItemR.get()->mResourceType))
                {
                    myItems[itemIndex].mQuantityOfItems--;
                    if (myItems[itemIndex].mQuantityOfItems < 1)
                    {
                        myItems.erase(myItems.begin() + itemIndex);
                    }
                }
            }

        }

    }

}

void Inventory::Unload()
{

    myItems.clear();

}
