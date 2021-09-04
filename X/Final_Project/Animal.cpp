#include "Animal.h"

float Animal::mXvelocity = 300.0f;

void Animal::Unload()
{
}

void Animal::Render()
{

	const X::Math::Vector2 screenPosition = XCamera::Get().ConverteToScreenPosition(mPosition);


	if (mActive)
	{
		X::DrawSprite(mTextureid, screenPosition);
	}

}

void Animal::Spawn(const X::Math::Vector2& spawnPosition)
{
	mPosition = spawnPosition;

	mVelocity = X::Math::Vector2(mXvelocity, 150.f);
	//Change the direction for next call
	mXvelocity *= -1;

	mActive = true;
}

void Animal::Kill()
{
	mActive = false;
}

