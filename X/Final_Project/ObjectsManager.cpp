#include "ObjectsManager.h"

namespace
{
    // Game Object resources
    std::unique_ptr<ObjectsManager> objManagerInstance = nullptr;
}


void ObjectsManager::StaticInitialize()
{

    XASSERT(objManagerInstance == nullptr, "Erro.. characterInstance has already an instance");
    objManagerInstance = std::make_unique<ObjectsManager>();

}

void ObjectsManager::StaticTerminate()
{
    objManagerInstance.reset();
}

ObjectsManager& ObjectsManager::Get()
{
    XASSERT(objManagerInstance != nullptr, "Erro.. characterInstance has not an instance yet");
    return*objManagerInstance;
}

void ObjectsManager::LoadAllResorces()
{

    LoadFoodVector();

    for (std::vector<Food>::iterator it = GameFoodResources.begin(); it != GameFoodResources.end(); it++)
    {
        it->Load();
        
    }

    LoadResourceVector();

    for (std::vector<Resource>::iterator it = GameResources.begin(); it != GameResources.end(); it++)
    {
        it->Load();

    }


}

void ObjectsManager::Unload()
{

    GameFoodResources.clear();
    GameResources.clear();

}

void ObjectsManager::Update(float deltaTime)
{

    //Update and render food assets
    for (std::vector<Food>::iterator it = GameFoodResources.begin(); it != GameFoodResources.end(); it++)
    {
        it->Render();
        it->Update(deltaTime);
    }

    //Update and render Resources assets
    for (std::vector<Resource>::iterator it = GameResources.begin(); it != GameResources.end(); it++)
    {
        it->Render();
        it->Update(deltaTime);
    }


}


//Load Images and propreties


void ObjectsManager::LoadFoodVector()
{
 
    GameFoodResources.emplace_back(2500, 80, FoodType::redfruits);
    GameFoodResources.emplace_back(800, 910, FoodType::redfruits);
    GameFoodResources.emplace_back(5700, 80, FoodType::redfruits);
    GameFoodResources.emplace_back(5600, 82, FoodType::redfruits);
    GameFoodResources.emplace_back(800, 82, FoodType::carrot);
    GameFoodResources.emplace_back(1800, 720, FoodType::carrot);
    GameFoodResources.emplace_back(400, 1050, FoodType::carrot);
    GameFoodResources.emplace_back(1300, 720, FoodType::orange);
    GameFoodResources.emplace_back(90, 600, FoodType::orange);
    GameFoodResources.emplace_back(4400, 645, FoodType::apple);
    GameFoodResources.emplace_back(6250, 400, FoodType::apple);
    GameFoodResources.emplace_back(4550, 302, FoodType::apple);

}

void ObjectsManager::LoadResourceVector()
{

   // Character::Get().SetPosition({ 3600, 1000 });

    // Hard Rock
    GameResources.emplace_back(360, 600, ResourceType::hardRock);
    GameResources.emplace_back(1460, 200, ResourceType::hardRock);
    GameResources.emplace_back(1850, 1100, ResourceType::hardRock);
    GameResources.emplace_back(1650, 1100, ResourceType::hardRock);
    GameResources.emplace_back(4350, 1100, ResourceType::hardRock);
    GameResources.emplace_back(4350, 700, ResourceType::hardRock);
    GameResources.emplace_back(5950, 600, ResourceType::hardRock);
    GameResources.emplace_back(700, 200, ResourceType::hardRock);

    // Wood 
    GameResources.emplace_back(1350, 1100, ResourceType::wood);
    GameResources.emplace_back(1350, 900, ResourceType::wood);
    GameResources.emplace_back(1350, 800, ResourceType::wood);
    GameResources.emplace_back(1250, 750, ResourceType::wood);
    GameResources.emplace_back(3250, 750, ResourceType::wood);
    GameResources.emplace_back(3850, 1050, ResourceType::wood);

    // Wood sticks for fire
    GameResources.emplace_back(1350, 1000, ResourceType::w_Sticks);
    GameResources.emplace_back(3350, 1000, ResourceType::w_Sticks);
    GameResources.emplace_back(4350, 500, ResourceType::w_Sticks);
    GameResources.emplace_back(2400, 900, ResourceType::w_Sticks);
    GameResources.emplace_back(5900, 900, ResourceType::w_Sticks);
    GameResources.emplace_back(1955, 1000, ResourceType::w_Sticks);
    GameResources.emplace_back(2050, 1030, ResourceType::w_Sticks);

    // Chipped Stone 

    GameResources.emplace_back(2600, 1030, ResourceType::chippedStone);
    GameResources.emplace_back(3600, 1030, ResourceType::chippedStone);
    GameResources.emplace_back(4700, 700, ResourceType::chippedStone);
    GameResources.emplace_back(2500, 900, ResourceType::chippedStone);
    GameResources.emplace_back(2300, 1030, ResourceType::chippedStone);
   
    // Spear Parts

    GameResources.emplace_back(5900, 85, ResourceType::spearShaft);
    GameResources.emplace_back(6000, 85, ResourceType::spearHead);


}
