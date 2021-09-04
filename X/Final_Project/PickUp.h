#pragma once
#include<XEngine.h>
#include "Character.h"


enum class PickupType {food, resource };

class PickUp
{

protected:


	
	X::TextureId mTextureid = 0;

	X::Math::Vector2 mPosition;
	X::SoundId pickUpSound;
	
	bool mActive = true;
	float mDelay = 0.0f;

	float mSpriteWidth = 0.0f;
	int mHealthRestore = 0;

public:



	PickupType pickupType;

	//Standard Object functions
	virtual void Load() = 0;
	void Unload();
	virtual void Update(float deltaTime);
	void Render();
	void RenderOnInventory(const char* info);

	//Class Special Functions
	void Spawn(float deltaTime);
	virtual void Collected() = 0;
		
	//Getters and Setters
	X::Math::Circle GetBoundingCircle()const { return X::Math::Circle(mPosition, (mSpriteWidth/2.0f)); }
	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	const X::Math::Vector2& GetPosition()const { return mPosition; }
	bool GetIsActice()const { return mActive; }

	bool CheckCollision();

};

