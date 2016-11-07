#include "GameBitmap.h"
#include "Direct2D.h"

template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

GameBitmap::GameBitmap(ID2D1Bitmap* bitmap)
{
	_bitmap = bitmap;
	_topLeft = { 0, 0 };
}

GameBitmap::~GameBitmap()
{
}

void GameBitmap::Draw()
{
}

void GameBitmap::SetPosition(float x, float y)
{
	_topLeft = D2D1::Point2F(x, y);
}

void GameBitmap::Transfer(float x, float y)
{
	_topLeft = D2D1::Point2F(_topLeft.x + x, _topLeft.y + y);
}
