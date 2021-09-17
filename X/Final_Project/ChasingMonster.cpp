#include "ChasingMonster.h"
#include "Character.h"

void ChasingMonster::Load()
{

	mTextureid = X::LoadTexture("Dude.png");

	mSpriteWidth = X::GetSpriteWidth(mTextureid);
	mSpriteHeight = X::GetSpriteHeight(mTextureid);
	mHalfSpriteWidth = mSpriteWidth / 2.0f;
	mHalfSpriteHeigh = mSpriteHeight / 2.0f;

	mDelay = 1.0f;

	mPosition = { 4450,600};

	mVelocity = X::Math::Vector2(0.0f, 0.0f);
	//Change the direction for next call
	
	mActive = true;


}

X::Math::Rect ChasingMonster::GetBoundingBox() const
{
	return {
	 mPosition.x - mHalfSpriteWidth,//Left
	 mPosition.y - mHalfSpriteHeigh,//Top
	 mPosition.x + mHalfSpriteWidth,//Right
	 mPosition.y + mHalfSpriteHeigh,//Bottom
	};
}

void ChasingMonster::Update(float deltaTime)
{

	

	if (mActive)
	{

        X::Math::Vector2 displacement; // every frame set to {0,0}

        mVelocity = Character::Get().GetPosition() - mPosition;

        if (mVelocity.x <= 0.0f)//Left
        {
            displacement.x -= mVelocity.x * deltaTime;
        }

        if (mVelocity.x >= 0.0f)//Right
        {
            displacement.x += mVelocity.x * deltaTime;
        }


        if (mVelocity.y <= 0.0f)//UP
        {
            displacement.y -= mVelocity.y * deltaTime;
        }

        if (mVelocity.y >= 0.0f)//Down
        {
            displacement.y += mVelocity.y * deltaTime;

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
                  //mVelocity.x = 0.0f;
                    mPosition += -mVelocity.x * deltaTime * acceleration;
                    isColiding = true;
                }
                else
                {
                    isColiding = false;
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
                   // mVelocity.x = 0.0f;
                    isColiding = true;
                    mPosition += -mVelocity.x * deltaTime * acceleration;
                }
                else
                {
                    isColiding = false;
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
                   // mVelocity.y = 0.0f;
                    isColiding = true;
                    mPosition += -mVelocity.y * deltaTime * acceleration;
                }
                else
                {
                    isColiding = false;
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
                    mVelocity.y = 0.0f;
                   // mPosition += -mVelocity.y * deltaTime * acceleration;

                    isColiding = true;
                }
                else
                {
                    isColiding = false;
                }
            }
        
            if (!isColiding)
            {
                mPosition += mVelocity * deltaTime * acceleration ;
            }
 
            //Check Boundries

            const uint32_t screenWidth = X::GetScreenWidth() * 5;
            const uint32_t screenHeight = X::GetScreenHeight() * 3;

            if (mPosition.x > screenWidth - mHalfSpriteWidth
                || mPosition.x < mHalfSpriteWidth)
            {
                mPosition = { 4450,600 };
            }

            if (mPosition.y > screenHeight )
            {
                mPosition = { 4450,600 };
            }

            if (mPosition.y < mHalfSpriteHeigh)
            {
                mPosition = { 4450,600 };
            }

       
	}

}
