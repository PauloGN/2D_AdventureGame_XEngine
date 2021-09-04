#include "XCamera.h"


namespace
{
    std::unique_ptr<XCamera> cameraInstance = nullptr;
}

void XCamera::StaticInitialize()
{

    XASSERT(cameraInstance == nullptr, "Erro.. camera has already an instance");
    cameraInstance = std::make_unique<XCamera>();

}

void XCamera::StaticTerminate()
{
    cameraInstance.reset();
}

XCamera& XCamera::Get()
{
    XASSERT(cameraInstance != nullptr, "Erro.. camera has not an instance yet");
    return*cameraInstance;
}

//=============================================== Regular Functions ======================================================


X::Math::Vector2 XCamera::ConverteToScreenPosition(const X::Math::Vector2& wolrdPosition) const
{
    return wolrdPosition - mOffset;
}

X::Math::Vector2 XCamera::ConverteToWorldPosition(const X::Math::Vector2& screenPosition) const
{
    return screenPosition + mOffset;
}

void XCamera::SetViewBound(const X::Math::Rect& viewBound)
{
    mViewBound = viewBound;

    const float screenWidth = static_cast<float>(X::GetScreenWidth());
    const float screenHeight = static_cast<float>(X::GetScreenHeight());

    if (mViewBound.right - mViewBound.left < screenWidth)
    {
        mViewBound.right = mViewBound.left + screenWidth;
    }

    if (mViewBound.bottom - mViewBound.top < screenHeight)
    {
        mViewBound.bottom = mViewBound.top + screenHeight;
    }

}

//viewPOsition receives what ever I am try to focus the camera on it
void XCamera::SetViewPosition(const X::Math::Vector2& viewPosition)
{

    const float screenWidth = static_cast<float>(X::GetScreenWidth());
    const float screenHeight = static_cast<float>(X::GetScreenHeight());

    const X::Math::Vector2 halfScreenSize{ screenWidth / 2.0f, screenHeight / 2.0f };

    // compute the position offSet

    mOffset = viewPosition - halfScreenSize;


    //Ensure Offset is within our view bound

    if (mOffset.x < mViewBound.left)
    {
        mOffset.x = mViewBound.left;
    }

    if (mOffset.y < mViewBound.top)
    {
        mOffset.y = mViewBound.top;
    }

    if (mOffset.x > mViewBound.right - screenWidth)
    {
        mOffset.x = mViewBound.right - screenWidth;
    }

    if (mOffset.y > mViewBound.bottom - screenHeight)
    {
        mOffset.y = mViewBound.bottom - screenHeight;
    }

}
