#include "GameManager.h"


namespace
{
	// An internal namespace to create the static variable that will be the only instantiation of the class and also responsible for managing all actions and calls of the objects from the other classes.
	std::unique_ptr<GameManager> GameInstance = nullptr;
}


void GameManager::GamePlay(float deltaTime)
{

	//Game Play
	//This function calls the ambient sound to be looped.
	X::PlaySoundLoop(backGroundSound); 

	TileMap::Get().Update(deltaTime);
	Character::Get().Update(deltaTime);


	XCamera::Get().SetViewBound(TileMap::Get().GetBounds());
	XCamera::Get().SetViewPosition(Character::Get().GetPosition());


	TileMap::Get().Render();

	//Pick UP
	ObjectsManager::Get().Update(deltaTime);

	// Game Over Conditions

	if (X::IsKeyPressed(X::Keys::P) || Character::Get().IsGameOver())
	{
		X::PlaySoundOneShot(gameOverSound);
		gs = GameStates::gameOver;
	}

	//Animal/enemies

	if (!Character::Get().isFirePlaced)
	{
		AnimalManager::Get().SpawnEnemies(deltaTime);
		AnimalManager::Get().EnemiesRenderAndUpdate(deltaTime);
		AnimalManager::Get().CheckCollision();
	}

	// Character / Inventory / Craft
	Character::Get().RenderFire(deltaTime);

	Character::Get().Render();

	if (Character::Get().isInventoryOpen)
	{
		Inventory::Get().Update();
		Inventory::Get().Render();
	}

	if (Character::Get().isCraftPanelOpen)
	{
		CraftPanel::Get().Update();
		CraftPanel::Get().Render();
	}

}

void GameManager::GameMenu()       //************************************************
{
	X::StopSoundLoop(backGroundSound);
	//Background menu image
	X::DrawSprite(textureId_StartMenu, { (float)X::GetScreenWidth() / 2, (float)X::GetScreenHeight() / 2 }); // change to * 0.5

}

void GameManager::GameOver()
{
	X::StopSoundLoop(backGroundSound);
	//Background menu image
	X::DrawSprite(textureId_GameOver, { (float)X::GetScreenWidth() / 2, (float)X::GetScreenHeight() / 2 });
}

void GameManager::GameControlMenu()
{
	//Background menu image
	X::DrawSprite(textureId_Controls, { (float)X::GetScreenWidth() / 2, (float)X::GetScreenHeight() / 2 });
}

void GameManager::RestartGame()
{

	//Character
	
	Character::Get().Unload();
	Character::Get().Load();
	
	//Game Object Manager

	ObjectsManager::Get().Unload();
	ObjectsManager::Get().LoadAllResorces();

	//Map
	
	TileMap::Get().Load("chapter_1.txt", "tile_Info01.txt");


	//Inventory / Craft
	Inventory::Get().Unload();
	CraftPanel::Get().Unload();

	//Animal

	AnimalManager::Get().CleanUp();
	AnimalManager::Get().LoadInsects();
}

//=========================================== Standard Functions ============================================================\\

void GameManager::Load()
{

	//Game Initialization

	textureId_StartMenu = X::LoadTexture("Game Menu.png");
	textureId_GameOver = X::LoadTexture("GameOver.png");
	textureId_Controls = X::LoadTexture("Controls.png");
	backGroundSound = X::LoadSound("background-music.wav");
	gameOverSound = X::LoadSound("game-over.wav");
	X::ShowSystemCursor(false);
	X::SetBackgroundColor(X::Colors::DarkGreen);
	gs = GameStates::startMenu;


	//Camera
	XCamera::StaticInitialize();

	//Character
	Character::StaticInitialize();
	Character::Get().Load();
	
	//Game Object Manager
	ObjectsManager::StaticInitialize();
	ObjectsManager::Get().LoadAllResorces();

	//Map
	TileMap::StaticInitialize();
	TileMap::Get().Load("chapter_1.txt", "tile_Info01.txt");

	//Inventory
	Inventory::StaticInitialize();
	Inventory::Get().Load();

	//Craft system
	CraftPanel::StaticInitialize();
	CraftPanel::Get().Load();

	//Animal

	AnimalManager::StaticInitialize();
	AnimalManager::Get().LoadInsects();
	

}

void GameManager::Unload()
{

	TileMap::Get().Unload();
	TileMap::StaticTerminate();
	Character::Get().Unload();

	XCamera::StaticTerminate();
	Character::StaticTerminate();

	//Pick Up

	ObjectsManager::Get().Unload();


	//Inventory
	Inventory::StaticTerminate();

	//Craft Unload and Terminate
	CraftPanel::Get().Unload();
	CraftPanel::StaticTerminate();

	//Animal
	AnimalManager::Get().CleanUp();
	AnimalManager::StaticTerminate();

}

void GameManager::Update(float deltaTime)
{

	switch (gs)
	{
	case GameStates::startMenu:
		GameMenu();
				
		if (X::IsKeyPressed(X::Keys::ENTER))
		{
			gs = GameStates::gamePlay;
		}
		else if (X::IsKeyPressed(X::Keys::T))
		{
			gs = GameStates::controlsMenu;
		}

		break;
	case GameStates::gameOver:

		GameOver();
		if (X::IsKeyPressed(X::Keys::ENTER))
		{
			RestartGame();
			gs = GameStates::startMenu;
		}

		break;
	case GameStates::gamePlay:

		GamePlay(deltaTime);

		break;
	case GameStates::gameWin:

		GameOver();
		if (X::IsKeyPressed(X::Keys::ENTER))
		{
			RestartGame();
			gs = GameStates::startMenu;
		}

		break;
		case GameStates::controlsMenu:

		GameControlMenu();
		if (X::IsKeyPressed(X::Keys::ENTER))
		{
			gs = GameStates::startMenu;
		}

		break;
	default:
		break;
	}
	

}


//=============================================== Singleton Func =============================================================\\

void GameManager::StaticInitialize()
{
	XASSERT(GameInstance == nullptr, "Erro.. GameInstance has already an instance");
	GameInstance = std::make_unique<GameManager>();
}

void GameManager::StaticTerminate()
{
	GameInstance.reset();
}

GameManager& GameManager::Get()
{
	XASSERT(GameInstance != nullptr, "Erro.. GameInstance has not an instance yet");
	return*GameInstance;
}

