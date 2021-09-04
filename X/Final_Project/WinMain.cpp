#include "GameManager.h"


void GameInit()
{

	GameManager::StaticInitialize();
	GameManager::Get().Load();

}

bool GameLoop(float deltaTime)
{

	GameManager::Get().Update(deltaTime);

	return X::IsKeyPressed(X::Keys::ESCAPE);
}


void GameCleanup()
{
	GameManager::Get().Unload();
	GameManager::Get().StaticTerminate();
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR,int)
{

	X::Start("xconfig.json");
	GameInit();


	X::Run(GameLoop);


	GameCleanup();
	X::Stop();

	return 0;

}