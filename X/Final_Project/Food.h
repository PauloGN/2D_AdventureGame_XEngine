#pragma once
#include "PickUp.h"

enum class FoodType{ carrot, orange, apple, redfruits };

class Food : public PickUp
{

private:

	

public:

	const int mMax = 4;
	FoodType mFoodtype;
	Food(const float& x, const float& y, FoodType foodtype = FoodType::carrot);
	const int& ReturnHealthRestore()const { return mHealthRestore; }
	
	void Load()override;

	void Collected() override;
	
};

