#pragma once
#include "Animal.h"
class Insect : public Animal
{

private:

	float mHalfSpriteHeigh;
	//checks the boss fight moment
	bool isIntheMap;

public:

	void Load() override;
	void Update(float deltaTime) override;

};

