#pragma once
#include<XEngine.h>
#include "TileMap.h"
#include "XCamera.h"
#include "UI.h"

enum class ToolType{ rockHammer, stoneAx, spear, fire,spearHead, spearShaft, none  };

struct Tool
{

	ToolType myTool = ToolType::none;
	int	durability = 0;
	X::TextureId mTextureId = 0;
	X::Math::Vector2 mToolPosition = 0;
	Tool(ToolType toolType, int sDurability, X::TextureId textureId) :myTool (toolType),durability(sDurability), mTextureId(textureId){}
	

	void MoreDurability()
	{
		durability += 12;
	}

};


class Character
{
private:

	static float delay;
	static float randomDelay;
	static float delayHealthControl;
	
	std::vector<Tool> toolVec;

	X::TextureId mTextureId = 0;
	size_t xMove = 0;
	size_t yMove = 0;
	bool isMoving = false;

	X::Math::Vector2 mPosition = 0;

	float mMoveSpeed = 0.0f;

	float mHalfSpriteWidth = 0.0f;
	float mHalfSpriteHeight = 0.0f;

	X::TextureId myAnimations[4][6];
	void Animation(float deltaTime, int );

	int mThirst;
	int mHunguer;
	int mHealth;

	bool isGameOver;
	//UI

	std::unique_ptr<UI> myUI;

public:

	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static Character& Get();

	static bool isInventoryOpen;
	static bool isCraftPanelOpen;
	bool isFirePlaced;


public:

	//standard object Functions

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	//Getters and Setters

	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	const X::Math::Vector2& GetPosition()const { return mPosition; }
	X::Math::Circle GetBoundingCircle()const { return X::Math::Circle(mPosition, mHalfSpriteWidth); }

	X::Math::Rect GetBoundingBox()const;

	//Actions and Functionalities
	bool Action()const { return X::IsKeyPressed(X::Keys::SPACE); }
	bool IsGameOver()const { return isGameOver;}

	void BreakRocks();
	void CutTree();
	void GetWater();
	void InventoryOpenAndClose();
	void CraftPanelOpenAndClose();
	void RestoreVitality(const int& rst);

	void DecreaseHunguerAndThirt(float deltaTime);

	void IncreaseOrDecreaseHealth();
	void TakeDamage(int dgm);


	// Struct Tool
	void AddTool(ToolType toolT, X::TextureId textureId);
	ToolType CharacterHasTool(const ToolType& toolT);
	bool HasTool2Win();
	void DecreaseDurability(ToolType toolT);
	const X::Math::Vector2& ReturnPositionToRenderTool(size_t index);
	void RenderMyToolInfo();
	
	//Sound Effects

	X::SoundId rockSoundEffect = 0;
	X::SoundId treeSoundEffect = 0;

	//Fire

	bool RenderFire(float deltaTime);
	

};

