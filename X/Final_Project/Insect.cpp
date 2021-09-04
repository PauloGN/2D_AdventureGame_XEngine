#include "Insect.h"


void Insect::Load()
{

	mTextureid = X::LoadTexture("bug.png");

	mSpriteWidth = X::GetSpriteWidth(mTextureid);
	mSpriteHeight = X::GetSpriteHeight(mTextureid);
	mHalfSpriteWidth = mSpriteWidth / 2.0f;
	mHalfSpriteHeigh = mSpriteHeight / 2.0f;

	mDelay = X::RandomFloat(0.3f, 2.0f);

}

void Insect::Update(float deltaTime)
{

	if (mActive)
	{
		mPosition += mVelocity * deltaTime;

		if (mDelay <= 0.5f)
		{
			mVelocity.x *= -1.0f;
		}

		mDelay -= deltaTime;
		if (mDelay <= 0.0f)
		{
			//flip the x and y value for our current velocity
			mVelocity.x *= -1.0f;
			mVelocity.y *= -1.0f;
						
			//Reset delay to a randon number between 1 and 3 seconds
			mDelay = X::RandomFloat(1.0f, 3.0f);
		}

		//Screen Bound check

		const uint32_t screenWidth = X::GetScreenWidth()*5;
		const uint32_t screenHeight = X::GetScreenHeight()*3;

		if (mPosition.x > screenWidth - mHalfSpriteWidth
			|| mPosition.x < mHalfSpriteWidth)
		{
			isIntheMap = true;
			mVelocity.x *= -1.0f;
		}

		if (mPosition.y > screenHeight - mHalfSpriteHeigh)
		{
			mVelocity.y *= -1.0f;
			isIntheMap = true;
		}

		if (mPosition.y < mHalfSpriteHeigh && isIntheMap == true)
		{
			mPosition.y = mHalfSpriteHeigh;
			mVelocity.y *= -1.0f;
		}


	}


}

