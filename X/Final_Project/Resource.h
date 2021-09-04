#pragma once
#include "PickUp.h"

enum class ResourceType {wood, hardRock, w_Sticks, chippedStone, spearShaft, spearHead};

class Resource :  public PickUp
{

private:


public:


	ResourceType mResourceType;
	const int mMax = 4;
	Resource(const float& x, const float& y, ResourceType resource = ResourceType::wood);
	void Load() override;
	void Collected() override;

};

