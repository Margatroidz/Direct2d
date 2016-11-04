#pragma comment(lib, "d2d1")
#pragma comment(lib, "windowscodecs")
#include <d2d1_2.h>
#include <d2d1_2helper.h>

class Direct2D
{
public:
	Direct2D();
	~Direct2D();
	HRESULT CreateDirect2dDevice(HWND hwnd);
	HRESULT Test();
	HRESULT Test2(int imageId);
private:
	HWND _hwnd;
	RECT rectangle;
	ID2D1Factory* _direct2dFactory;
	ID2D1HwndRenderTarget* _direct2dRenderTarget;
	HRESULT LoadResourceBitmap(
		ID2D1RenderTarget *pRenderTarget,
		IWICImagingFactory *pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap **ppBitmap);
};