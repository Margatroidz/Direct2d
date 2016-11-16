#include <d2d1_2.h>
#include <d2d1_2helper.h>

class Image;
class Direct2D
{
public:
	static Direct2D* Instance();
	HRESULT CreateDirect2dDevice(HWND hwnd);
	ID2D1Bitmap* LoadBitmap(int resourceNumber);
	ID2D1Bitmap* LoadBitmap(char* resourceName);
	void DestroyBitmap(ID2D1Bitmap* image);
	void BeginLoad();
	void EndLoad();
	void BeginDraw();
	void EndDraw();
	void Draw(Image* image);
private:
	Direct2D();
	~Direct2D();
	ID2D1Bitmap* LoadBitmap(PCWSTR resourceName);
	HWND _hwnd;
	ID2D1Factory* _direct2dFactory;
	ID2D1HwndRenderTarget* _direct2dRenderTarget;
	IWICImagingFactory *_wicFactory;
	RECT _renderArea;
};
