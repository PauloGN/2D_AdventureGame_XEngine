#pragma once
#include <XEngine.h>
#include "XCamera.h"

class Animal
{

protected:

	static float mXvelocity;

	X::TextureId mTextureid = 0;

	X::Math::Vector2 mPosition;
	X::Math::Vector2 mVelocity;

	bool mActive = false;
	float mDelay = 0.0f;
	float mHalfSpriteWidth = 0.0f;
	float mSpriteWidth = 0.0f;
	float mSpriteHeight = 0.0f;



public:

	//Standard Object functions
	virtual void Load() = 0;
	void Unload();
	virtual void Update(float deltaTime) = 0;
	void Render();

	//Class Special Functions
	void Spawn(const X::Math::Vector2& spawnPosition);
	void Kill();
	X::Math::Circle GetBoundingCircle()const { return X::Math::Circle(mPosition, mHalfSpriteWidth); }


	//Getters and Setters
	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	const X::Math::Vector2& GetPosition()const { return mPosition; }
	bool GetIsActice()const { return mActive; }

};

