#pragma once
#include "XCamera.h"
#include "TileMap.h"
#include "Character.h"
#include "ObjectsManager.h"
#include "Inventory.h"
#include "CraftPanel.h"
#include "AnimalManager.h"


enum class GameStates { startMenu, gameOver, gamePlay, gameWin, controlsMenu };

class GameManager
{
private:
	
	//Game elements
	X::TextureId textureId_StartMenu = 0; // Back Ground Image
	X::TextureId textureId_GameOver = 0; // Back Ground Image
	X::TextureId textureId_Controls = 0; // Back Ground Image
	X::TextureId textureId_WinMenu = 0; // Back Ground Image
	X::SoundId backGroundSound = 0;
	X::SoundId gameOverSound = 0;
	GameStates gs;


	void GamePlay(float deltaTime);
	void GameMenu();
	void GameWin();
	void GameOver();
	void GameControlMenu();
	void RestartGame();


public:


	void Load();
	void Unload();
	void Update(float deltaTime);


public:

	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static GameManager& Get();


};

