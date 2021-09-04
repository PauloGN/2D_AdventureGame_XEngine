#pragma once
#include"XEngine.h"

class XCamera
{
public:
	//Sigleton functions

	static void StaticInitialize();
	static void StaticTerminate();
	static XCamera& Get();

public:

	X::Math::Vector2 ConverteToScreenPosition(const X::Math::Vector2& wolrdPosition)const;
	X::Math::Vector2 ConverteToWorldPosition(const X::Math::Vector2& screenPosition)const;

	void SetViewBound(const X::Math::Rect& viewBound);
	void SetViewPosition(const X::Math::Vector2& viewPosition);


private:

	X::Math::Rect mViewBound{ -FLT_MAX, -FLT_MAX, FLT_MAX, FLT_MAX };
	X::Math::Vector2 mOffset;

};


