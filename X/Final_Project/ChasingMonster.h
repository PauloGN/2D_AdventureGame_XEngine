#pragma once
#include "Animal.h"
class ChasingMonster : public Animal
{

	float mHalfSpriteHeigh;
	float mHalfSpriteWidth;
	//checks the limit of the map
	bool isIntheMap;
	float acceleration = 0.2f;
	X::Math::Rect GetBoundingBox()const;
	bool isColiding = false;
	float mDelay = 0.0f;

public:
	
	void Load() override;
	void Update(float deltaTime) override;

};

