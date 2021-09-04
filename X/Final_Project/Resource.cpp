#include "Resource.h"
#include "Inventory.h"

Resource::Resource(const float& x, const float& y, ResourceType resource):mResourceType(resource)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Resource::Load()
{
	switch (mResourceType)
	{
	case ResourceType::wood:

		mTextureid = X::LoadTexture("Wood.png");
	

		break;
	case ResourceType::hardRock:

		mTextureid = X::LoadTexture("HardRock.png");


		break;

	case ResourceType::w_Sticks:

		mTextureid = X::LoadTexture("WoodenSticks.png");

		break;

	case ResourceType::chippedStone:

		mTextureid = X::LoadTexture("Chipped stone.png");

		break;
	case ResourceType::spearShaft:

		mTextureid = X::LoadTexture("spearShaft.png");

		break;

	case ResourceType::spearHead:

		mTextureid = X::LoadTexture("spearHead.png");

		break;

	default:
		break;
	}

	pickupType = PickupType::resource;
	pickUpSound = X::LoadSound("PickUp.wav");
}


void Resource::Collected()
{

	if (Inventory::Get().AddItemsResource(mResourceType))
	{
		X::PlaySoundOneShot(pickUpSound);
		mActive = false;
	}

}

