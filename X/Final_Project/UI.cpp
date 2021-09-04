#include "UI.h"

void UI::Load()
{
	mTextureId = X::LoadTexture("UI.png");
	mScreenPosition = { 110.0f,50.0f };
}

void UI::Unload()
{
}

void UI::Update(float deltaTime)
{
}

void UI::DisplayInfo(int& thirst, int& hunger, int& health)
{
	const std::string thirstSTR(std::to_string(thirst));
	const std::string hungerSTR(std::to_string(hunger));
	const std::string healthSTR(std::to_string(health));

	X::DrawScreenText(thirstSTR.c_str(), 135, 25, 14, X::Colors::White);
	X::DrawScreenText(hungerSTR.c_str(), 152, 42, 14, X::Colors::White);
	X::DrawScreenText(healthSTR.c_str(), 138, 57, 14, X::Colors::White);

}

void UI::Render(int& thirst, int& hunger, int& health)
{
	X::DrawSprite(mTextureId, mScreenPosition);
	DisplayInfo(thirst,hunger,health);
}
