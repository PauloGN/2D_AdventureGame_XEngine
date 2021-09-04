#include "AnimalManager.h"
#include "Character.h"

namespace
{

	// Enemies /Animal Manager
	std::unique_ptr<AnimalManager> animalManagerInstance = nullptr;

	//insects

	constexpr int maxEnemies = 100;
	int currentEnemyIndex = 0;
		
}

void AnimalManager::StaticInitialize()
{

	XASSERT(animalManagerInstance == nullptr, "Erro.. AnimalManager has already an instance");
	animalManagerInstance = std::make_unique<AnimalManager>();

}

void AnimalManager::StaticTerminate()
{

	
	animalManagerInstance.reset();

}

AnimalManager& AnimalManager::Get()
{
	XASSERT(animalManagerInstance != nullptr, "Erro.. animalManagerInstance has not an instance yet");
	return*animalManagerInstance;
}

void AnimalManager::LoadInsects()
{

	insects = std::make_unique<Insect[]>(maxEnemies);
	monster = std::make_unique<ChasingMonster>();

	for (int i = 0; i < maxEnemies; i++)
	{
		insects[i].Load();
	}

	monster.get()->Load();
	//monster.get()->Spawn({ 1250,800 });
}

void AnimalManager::CleanUp()
{

	for (int i = 0; i < maxEnemies; i++)
	{
		insects[i].Kill();
	}

	insects.reset();
	monster.reset();
}

void AnimalManager::EnemiesRenderAndUpdate(float deltaTime)
{
	for (int i = 0; i < maxEnemies; i++)
	{
		insects[i].Render();
		insects[i].Update(deltaTime);
	}

	monster.get()->Update(deltaTime);
	monster.get()->Render();

}

void AnimalManager::SpawnEnemies(float deltaTime)
{

	const float spawnX = static_cast<float>(X::GetScreenWidth()) * X::RandomFloat(1, 3);
	const float spawnY = -100.0f;

	if (!insects[currentEnemyIndex].GetIsActice())
	{

		insects[currentEnemyIndex].Spawn({ spawnX,spawnY });
		currentEnemyIndex++;

		if (currentEnemyIndex >= maxEnemies)
		{
			currentEnemyIndex = 0;
		}
			
	}

}

void AnimalManager::CheckCollision()
{

	const X::Math::Circle CharacterCircle = Character::Get().GetBoundingCircle();

	for (int i = 0; i < maxEnemies; i++)
	{
		Insect& currentEnemy = insects[i];
		if (currentEnemy.GetIsActice())
		{

			const X::Math::Circle enemyCircle = currentEnemy.GetBoundingCircle();

			const float distanceEF = X::Math::Distance(enemyCircle.center, CharacterCircle.center);
			const float radiiEF = enemyCircle.radius + CharacterCircle.radius;

			if (distanceEF <= radiiEF)
			{

				Character::Get().TakeDamage(5);
				currentEnemy.Kill();

			}


		}
	}
}
