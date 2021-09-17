#include "PickUp.h"
#include "XCamera.h"


void PickUp::Unload()
{
}

void PickUp::Update(float deltaTime)
{

	CheckCollision();


	if (!mActive)
	{
		Spawn(deltaTime);
	}


}

void PickUp::Render()
{
	if (mActive)
	{
		const X::Math::Vector2 screenPosition = XCamera::Get().ConverteToScreenPosition(mPosition);

		X::DrawSprite(mTextureid, screenPosition);
	}
}

void PickUp::RenderOnInventory(const char* info)
{
	X::DrawSprite(mTextureid, mPosition);
	X::DrawScreenText(info,mPosition.x,mPosition.y + 8,14,X::Colors::White);
}


void PickUp::Spawn(float deltaTime)
{

	mDelay += deltaTime;

	if (mDelay > 30)
	{
		mActive = true;
		mDelay = 0.0f;
	}

	
}


bool PickUp::CheckCollision()
{
	const bool actionB = Character::Get().Action();


	
	if (mActive)
	{
		const X::Math::Circle character = Character::Get().GetBoundingCircle();
		const X::Math::Circle pickup = GetBoundingCircle();

		const float distanceEF = X::Math::Distance(pickup.center, character.center);
		const float radiiEF = pickup.radius + character.radius;


		if (distanceEF <= radiiEF)
		{
			const X::Math::Vector2 screenPosition = XCamera::Get().ConverteToScreenPosition(mPosition);
			X::DrawScreenText("Press Space to collect the item",screenPosition.x + 10,screenPosition.y , 14, X::Colors::White);
			
			if (actionB)
			{
				Collected();
			}

			return true;
		}
		
	}

	return false;

}