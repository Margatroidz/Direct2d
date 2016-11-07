#pragma comment(lib, "d2d1")
#pragma comment(lib, "windowscodecs")
#include <d2d1_2.h>

class GameBitmap 
{
public:
	void Draw();
	void SetPosition(float x, float y);
	void Transfer(float x, float y);
	friend class Direct;
private:
	GameBitmap(ID2D1Bitmap* bitmap);
	virtual ~GameBitmap();
	ID2D1Bitmap* _bitmap;
	D2D1_POINT_2F _topLeft;
};