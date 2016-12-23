#include <d2d1_2.h>
#include <d2d1_2helper.h>

class Image;
class Direct2D
{
public:
	Direct2D(const Direct2D&) = delete;
	Direct2D& operator=(const Direct2D&) = delete;
	static Direct2D* Instance();
	HRESULT CreateDirect2dDevice(HWND hwnd);
	ID2D1Bitmap* LoadBitmapD(int resourceNumber);
	ID2D1Bitmap* LoadBitmapD(char* resourceName);
	void DestroyBitmap(ID2D1Bitmap* image);
	void BeginLoad();
	void EndLoad();
	void BeginDraw();
	void EndDraw();
	void Rotate(D2D1::Matrix3x2F matrix);
	void DrawBitmap(ID2D1Bitmap* _bitmap, D2D1_RECT_F rect, float opacity);
	void DrawTextD(wchar_t* text, IDWriteTextFormat* format, ID2D1Brush* brush);
	void DestroyText(IDWriteTextFormat* format, ID2D1Brush* brush);
	IDWriteTextFormat* CreateTextFormat(char* format, int size);
	ID2D1SolidColorBrush* CreateBrush();
private:
	Direct2D();
	~Direct2D();
	ID2D1Bitmap* LoadBitmapD(PCWSTR resourceName);
	HWND _hwnd;
	ID2D1Factory* _direct2dFactory;
	ID2D1HwndRenderTarget* _direct2dRenderTarget;
	IWICImagingFactory *_wicFactory;
	RECT _renderArea;
};