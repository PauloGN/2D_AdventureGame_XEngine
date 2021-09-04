#include "Food.h"
#include "Inventory.h"

Food::Food(const float& x, const float& y, FoodType foodtype) : mFoodtype(foodtype)
{

	mPosition.x = x;
	mPosition.y = y;

}

void Food::Load()
{

	switch (mFoodtype)
	{
	case FoodType::carrot:

		mTextureid = X::LoadTexture("Carrot.png");
	
		mHealthRestore = 10;
		break;
	case FoodType::orange:
		
		mTextureid = X::LoadTexture("Orange.png");
	
		mHealthRestore = 10;

		break;
	case FoodType::apple:

		mTextureid = X::LoadTexture("Apple.png");
	
		mHealthRestore = 10;

		break;
	case FoodType::redfruits:

		mTextureid = X::LoadTexture("RedFruit.png");
	
		mHealthRestore = 15;

		break;
	default:
		break;
	}
	

	pickupType = PickupType::food;
	pickUpSound = X::LoadSound("PickUp.wav");
	
	mSpriteWidth = X::GetSpriteWidth(mTextureid);

}

void Food::Collected()
{
	
	if (Inventory::Get().AddItemsFood(mFoodtype)) {
	
		X::PlaySoundOneShot(pickUpSound);
		mActive = false;
	}
	

}


