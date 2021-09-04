#pragma once
#include<vector>
#include"Food.h"
#include "Resource.h"


class ObjectsManager
{

public:
	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static ObjectsManager& Get();

public:

	void LoadAllResorces();
	void Unload();
	virtual void Update(float deltaTime);


private:

	std::vector <Food> GameFoodResources;
	std::vector <Resource> GameResources;


	//Loads
	void LoadFoodVector();
	void LoadResourceVector();



};

