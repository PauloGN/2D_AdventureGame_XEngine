#include "Character.h"

bool Character::isInventoryOpen = false;
bool Character::isCraftPanelOpen = false;
float Character::delay = 0;
float Character::delayHealthControl = 30;
float Character::randomDelay = 5;


namespace
{
    std::unique_ptr<Character> characterInstance = nullptr;
}


void Character::StaticInitialize()
{

    XASSERT(characterInstance == nullptr, "Erro.. characterInstance has already an instance");
    characterInstance = std::make_unique<Character>();
    
}

void Character::StaticTerminate()
{

    characterInstance.reset();
}

Character& Character::Get()
{
    XASSERT(characterInstance != nullptr, "Erro.. characterInstance has not an instance yet");
    return* characterInstance;
}

//========================================================================================================================\\

void Character::Animation(float deltaTime, int direction)
{
    

    delay += deltaTime;
    xMove = direction;

    if (delay > 0.0f)
    {
        yMove = 0;
        delay += deltaTime;

        if (delay >0.5f)
        {
            yMove = 1;
            delay += deltaTime;

            if (delay > 1.0f)
            {
                yMove = 2;
                delay += deltaTime;

                if (delay > 1.5f)
                {
                    yMove = 3;
                    delay += deltaTime;
                   

                    if (delay > 2.0f)
                    {
                        yMove = 4;
                        delay += deltaTime;
                        
                        if (delay > 2.5f)
                        {
                            yMove = 5;
                            delay += deltaTime;
                            delay = 0;
                        }
                    }

                }
            }
        }
    }

   
}


void Character::Load()
{

    // ================ load Variables ================\\

    mTextureId = X::LoadTexture("R_Idle_01.png");
    mMoveSpeed = 200.0f;

    mHalfSpriteHeight = X::GetSpriteHeight(mTextureId) / 2.0f;
    mHalfSpriteWidth = X::GetSpriteWidth(mTextureId) / 2.0f;

    mHunguer = 100;
    mThirst = 100;
    mHealth = 100;
    
    mPosition = {1250,800};

    isGameOver = false;
    isInventoryOpen = false;
    isCraftPanelOpen = false;
    isFirePlaced = false;

    rockSoundEffect = X::LoadSound("B_Rock.wav");
    treeSoundEffect = X::LoadSound("TreeSound.wav");
    //================== load animations ===============\\

    for (size_t i = 0; i < 6; i++)
    {
        std::string str[4] = { "R_Back_0","R_Go_L_0","R_Walk_0","R_Go_R_0" };
        std::stringstream ss;
        ss << i+1;
        std::string idx;
        ss >> idx;
        for (size_t j = 0; j < 4; j++)
        {
         str[j] += idx + ".png";
         myAnimations[j][i] = X::LoadTexture(str[j].c_str());
        }

    }

    //====================== load UI ======================\\
    
    myUI = std::make_unique<UI>();
    myUI.get()->Load();

}


void Character::Unload()
{

    toolVec.clear();

}


void Character::Update(float deltaTime)
{

    // Generic movement Strategy when AABB colligision is involved
    // - Predict what the displacement Will be based on player input
    // - Check for collision
    // - if colligion occurs, set displacement to -> zero
    // - Add displacement to the position
    
//Check for player input and record amount of displacement

    X::Math::Vector2 displacement; // every frame set to {0,0}
   
    bool isMovingToSide = false;

    if (X::IsKeyDown(X::Keys::A))//Left
    {
        displacement.x -= mMoveSpeed * deltaTime;

        isMoving = true;
        isMovingToSide = true;
        Animation(deltaTime, 1);
    }

    if (X::IsKeyDown(X::Keys::D))//Right
    {
        displacement.x += mMoveSpeed * deltaTime;
        
        isMoving = true;
        isMovingToSide = true;
        Animation(deltaTime, 3);
    }

    
    if (X::IsKeyDown(X::Keys::W))//UP
    {
        displacement.y -= mMoveSpeed * deltaTime;
      
      isMoving = true;

      if (!isMovingToSide)
      {
          Animation(deltaTime,0);
      }

    }

    if (X::IsKeyDown(X::Keys::S))//Down
    {
        displacement.y += mMoveSpeed * deltaTime;

        isMoving = true;

        if (!isMovingToSide)
        {
            Animation(deltaTime, 2);
        }

    }

 
    //Checking for collision

    const X::Math::Rect currentBoundingBox = GetBoundingBox();


    //Right Edge -- trying to move to the right

    if (displacement.x > 0.0f)
    {

        X::Math::LineSegment rightEdge{
            currentBoundingBox.max.x + displacement.x,
            currentBoundingBox.min.y,
            currentBoundingBox.max.x + displacement.x,
            currentBoundingBox.max.y
        };

        if (TileMap::Get().IsCollidingWith(rightEdge))
        {
            displacement.x = 0.0f;
            
            // se acçao, e se ferramenta , pega a localização e muda o tile 
            // dentro da classe mapa a variavel tileIndex pega a localização

        }
    }

    //Left Edge -- trying to move to the left

    if (displacement.x < 0.0f)
    {

        X::Math::LineSegment leftEdge{
            currentBoundingBox.min.x + displacement.x,
            currentBoundingBox.min.y,
            currentBoundingBox.min.x + displacement.x,
            currentBoundingBox.max.y
        };

        if (TileMap::Get().IsCollidingWith(leftEdge))
        {
            displacement.x = 0.0f;
        }
    }

    //Bottom Edge -- trying to move downwards

    if (displacement.y > 0.0f)
    {

        X::Math::LineSegment bottomEdge{
            currentBoundingBox.min.x,
            currentBoundingBox.max.y + displacement.y,
            currentBoundingBox.max.x,
            currentBoundingBox.max.y + displacement.y
        };

        if (TileMap::Get().IsCollidingWith(bottomEdge))
        {
            displacement.y = 0.0f;
        }
    }

    //TopEdge -- trying to move Upwards

    if (displacement.y < 0.0f)
    {

        X::Math::LineSegment topEdge{
            currentBoundingBox.min.x,
            currentBoundingBox.min.y + displacement.y,
            currentBoundingBox.max.x,
            currentBoundingBox.min.y + displacement.y
        };

        if (TileMap::Get().IsCollidingWith(topEdge))
        {
            displacement.y = 0.0f;
        }
    }

    //Add displacement to the position
    mPosition += displacement;

    //Functionalities and character actions
    if (Action())
    {
        BreakRocks();
        GetWater();
        CutTree();
    }
    
    InventoryOpenAndClose();
    CraftPanelOpenAndClose();
    DecreaseHunguerAndThirt(deltaTime);
}

void Character::Render()
{
    const X::Math::Vector2 screenPosition = XCamera::Get().ConverteToScreenPosition(mPosition);


    if (isMoving)
    {
        X::DrawSprite(myAnimations[xMove][yMove], screenPosition);
    }
    else
    {
        X::DrawSprite(mTextureId, screenPosition);
    }

    //Renderin UI
    myUI.get()->Render(mThirst,mHunguer,mHealth);
    // Tool
    RenderMyToolInfo();
}

X::Math::Rect Character::GetBoundingBox() const
{
    return {
     mPosition.x - mHalfSpriteWidth,//Left
     mPosition.y - mHalfSpriteHeight,//Top
     mPosition.x + mHalfSpriteWidth,//Right
     mPosition.y + mHalfSpriteHeight,//Bottom
    };
}

void Character::BreakRocks()
{

    const ToolType myTool = CharacterHasTool(ToolType::rockHammer);

    
    if (myTool == ToolType::rockHammer)
    {
        const int currentMapIndex = TileMap::Get().MapCurrentCollisionIndex(); // Location 
        const int currentTile  = TileMap::Get().MapCurrentTileIndex(); // Sprite
        
         if (currentTile >= 18 && currentTile <= 21)
         {
             const bool decreaseH = TileMap::Get().SetMapIndexTile(currentMapIndex);
             if (decreaseH)
             {
                 X::PlaySoundOneShot(rockSoundEffect);
                 DecreaseDurability(ToolType::rockHammer);
             }
         }
    }
    
}

void Character::CutTree()
{
    const ToolType myTool = CharacterHasTool(ToolType::stoneAx);

    if (myTool == ToolType::stoneAx)
    {
        const int currentMapIndex = TileMap::Get().MapCurrentCollisionIndex(); //Location
        const int currentTile = TileMap::Get().MapCurrentTileIndex(); // Sprite

        if (currentTile >= 36 && currentTile <= 39)
        {

            const bool decrease = TileMap::Get().SetMapIndexTile(currentMapIndex);
            if (decrease)
            {
                X::PlaySoundOneShot(treeSoundEffect);
                DecreaseDurability(ToolType::stoneAx);
            }
        }
    }

}

void Character::GetWater()
{
    const int currentMapIndex = TileMap::Get().MapCurrentTileIndex();

    if (currentMapIndex == 22)
    {
        mThirst += 10;

        if (mThirst >= 100)
        {
            mThirst = 100;
        }
    }

}

void Character::InventoryOpenAndClose()
{
    if (X::IsKeyPressed(X::Keys::I))
    {
        isInventoryOpen = !isInventoryOpen;

        if (!isInventoryOpen)
        {
            isCraftPanelOpen = false;
        }
    }
}

void Character::CraftPanelOpenAndClose()
{
    if (X::IsKeyPressed(X::Keys::C))
    {
        isCraftPanelOpen = !isCraftPanelOpen;
        if (isCraftPanelOpen)
        {
            isInventoryOpen = true;
        }
        if (!isCraftPanelOpen)
        {
            isInventoryOpen = false;
        }
    }

}

void Character::RestoreVitality(const int& rst)
{

    mThirst += 2;
    mHunguer += rst;

    if (mThirst >= 100)
    {
        mThirst = 100;
    }

    if (mHunguer >= 100)
    {
        mHunguer = 100;

    }

}

void Character::DecreaseHunguerAndThirt(float deltaTime)
{

    delayHealthControl -= deltaTime;

    if (delayHealthControl <= 0)
    {
        mHunguer -= 5;
        mThirst -= 7;
        
        if (mHunguer <= 0)
        {
            mHunguer = 0;
        }

        if (mThirst <= 0)
        {
            mThirst = 0;
        }
        IncreaseOrDecreaseHealth();
        delayHealthControl = 30;
    }

}

void Character::IncreaseOrDecreaseHealth()
{

    if (mThirst >= 70 && mHunguer >= 70)
    {
        mHealth += 5;

        if (mHealth >= 100)
        {
            mHealth = 100;
        }
        return;
    }

    if (mThirst <= 0 || mHunguer <= 0)
    {
        mHealth -= 35;

    }
    else if (mThirst <= 20 || mHunguer <= 10)
    {
        mHealth -= 25;
    }
    else if (mThirst <= 30 || mHunguer <= 20 )
    {
        mHealth -= 10;
    }

    if (mHealth <= 0)
    {
        mHealth = 0;
        isGameOver = true;
    }

}

void Character::TakeDamage(int dmg)
{

    mHealth -= dmg;

    if (mHealth <= 0)
    {
        mHealth = 0;
        isGameOver = true;
    }

}

//====================  Struct Tool Functions =====================================\\

void Character::AddTool(ToolType toolT, X::TextureId textureId)
{


       for (auto it = toolVec.begin(); it != toolVec.end(); it++)
       {

           if (it->myTool == toolT)
           {
               it->MoreDurability();
               return;
           }
       }
    

    toolVec.emplace_back(toolT, 10,textureId);

}

ToolType Character::CharacterHasTool(const ToolType& toolT)
{
    
    if (!toolVec.empty())
    {
        for (auto &iten : toolVec)
        {

            if (iten.myTool == toolT && iten.durability > 0 )
            {
                return iten.myTool;
            }
        }
    }

    return ToolType::none;
}


void Character::DecreaseDurability(ToolType toolT)
{

    if (!toolVec.empty())
    {
        for (std::vector<Tool>::iterator it = toolVec.begin(); it != toolVec.end(); it++)
        {

            if (it->myTool == toolT && it->durability > 0)
            {
                it->durability--;
                if (it->durability < 1)
                {
                    toolVec.erase(it);
                    break;
                }
            }
        }
    }

}

const X::Math::Vector2& Character::ReturnPositionToRenderTool(size_t index)
{
    X::Math::Vector2 position;
    switch (index)
    {
    case 0:

        position = { 245.0f, 45.0f };

        break;
    case 1:
        position = { 295.0f,45.0f };
        break;
    case 2:
        position = { 345.0f,45.0f };
        break;
    case 3:
        position = { 395.0f,45.0f };
        break;

    default:

        break;
    }

    return position;
}

void Character::RenderMyToolInfo()
{
    if (!toolVec.empty())
    {
        for (size_t i = 0; i < toolVec.size(); i++)
        {

            X::DrawSprite(toolVec[i].mTextureId, ReturnPositionToRenderTool(i));

            const float x = ReturnPositionToRenderTool(i).x;
            const float y = ReturnPositionToRenderTool(i).y + 8;

            const std::string durability(std::to_string(toolVec[i].durability));
            X::DrawScreenText(durability.c_str(), x, y, 14, X::Colors::White);

        }
    }

}

bool Character::RenderFire(float deltaTime)
{
    
    if (!toolVec.empty())
    {
        
        for (size_t i = 0; i < toolVec.size(); i++)
        {

            if (toolVec[i].myTool == ToolType::fire)
            {
                if (!isFirePlaced)
                {
                    toolVec[i].mToolPosition = mPosition;
                    isFirePlaced = true;
                }

                 const X::Math::Vector2 screenPosition = XCamera::Get().ConverteToScreenPosition(toolVec[i].mToolPosition)+8;
                 X::DrawSprite(toolVec[i].mTextureId, screenPosition);
                
                 randomDelay -= deltaTime;
                                 
                 if (randomDelay <= 0)
                 {
                     DecreaseDurability(ToolType::fire);
                     randomDelay = 5;
                 }

                 return true;
            }
        }
    }

    isFirePlaced = false;
    return false;
}

