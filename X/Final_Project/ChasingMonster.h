#pragma once
#include "Animal.h"
class ChasingMonster : public Animal
{

	float mHalfSpriteHeigh;
	//checks the limit of the map
	bool isIntheMap;

public:

	void Load() override;
	void Update(float deltaTime) override;

};

