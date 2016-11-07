#pragma comment(lib, "d2d1")
#pragma comment(lib, "windowscodecs")
#include <d2d1_2.h>
#include <d2d1_2helper.h>

class GameBitmap;
class Direct
{
public:
	static Direct* Instance();
	HRESULT CreateDirect2dDevice(HWND hwnd);
	GameBitmap* LoadResourceBitmap(int resourceNumber);
	GameBitmap* LoadResourceBitmap(PCWSTR resourceName);
	void DestroyResourceBitmap(GameBitmap* gameBitmap);
	void BeginLoad();
	void EndLoad();
	void BeginDraw();
	void EndDraw();
	void Draw(GameBitmap* bitmap);
	HRESULT Test();
	HRESULT Test2(int imageId);
private:
	Direct();
	~Direct();
	HWND _hwnd;
	ID2D1Factory* _direct2dFactory;
	ID2D1HwndRenderTarget* _direct2dRenderTarget;
	IWICImagingFactory *_wicFactory;
	RECT _renderArea;
};