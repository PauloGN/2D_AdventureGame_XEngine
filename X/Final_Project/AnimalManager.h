#pragma once
#include"Insect.h"
#include "ChasingMonster.h";
class AnimalManager
{

private:


	std::unique_ptr<Insect[]> insects = nullptr;
	std::unique_ptr<ChasingMonster> monster = nullptr;

public:

	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static AnimalManager& Get();


	//Insect

	
	void LoadInsects();
	void CleanUp();
	void EnemiesRenderAndUpdate(float deltaTime);
	void SpawnEnemies(float deltaTime);
	void CheckCollision();
};

