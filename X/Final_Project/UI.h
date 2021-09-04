#pragma once
#include<XEngine.h>

class UI
{

private:

		

	X::TextureId mTextureId = 0;
	X::Math::Vector2 mScreenPosition;


public:

	void Render(int& thirst, int& hunger, int& health);
	void Load();
	void Unload();
	void Update(float deltaTime);
	
	void DisplayInfo(int& thirst, int& hunger,int& health);


};

