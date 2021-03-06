#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "windowscodecs")
#include "Direct2D.h"
#include <wrl/client.h>
#include <wincodec.h>
#include <memory>
#include <dwrite.h>
#define ASSERT(hr) if(!SUCCEEDED(hr)){ throw hr; }

template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != nullptr)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = nullptr;
	}
}

Direct2D::Direct2D()
{
	_hwnd = nullptr;
	_direct2dFactory = nullptr;
	_direct2dRenderTarget = nullptr;
	_wicFactory = nullptr;
}

Direct2D::~Direct2D()
{
	SafeRelease(&_direct2dFactory);
	SafeRelease(&_direct2dRenderTarget);
	SafeRelease(&_wicFactory);
}

Direct2D* Direct2D::Instance()
{
	static Direct2D instance;
	return &instance;
}

HRESULT Direct2D::CreateDirect2dDevice(HWND hwnd)
{
	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	ASSERT(hr);

	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&_wicFactory);
	ASSERT(hr);

	_hwnd = hwnd;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_direct2dFactory);
	ASSERT(hr);

	RECT rc;
	hr = GetClientRect(_hwnd, &rc);
	_direct2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			_hwnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
		), &_direct2dRenderTarget);
	ASSERT(hr);

	return hr;
}

ID2D1Bitmap* Direct2D::LoadBitmapD(char* sourcePath)
{
	ID2D1Bitmap* bitmap = nullptr;
	IWICBitmapDecoder* decoder = nullptr;
	IWICBitmapFrameDecode *bitmapSource = nullptr;
	IWICFormatConverter *converter = nullptr;

	int length = strlen(sourcePath) + 1;
	wchar_t* wPath = new wchar_t[length];
	mbstowcs_s(0, wPath, length, sourcePath, _TRUNCATE);
	_wicFactory->CreateDecoderFromFilename(wPath, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
	decoder->GetFrame(0, &bitmapSource);
	_wicFactory->CreateFormatConverter(&converter);
	converter->Initialize(bitmapSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeMedianCut);
	ASSERT(_direct2dRenderTarget->CreateBitmapFromWicBitmap(converter, nullptr, &bitmap));

	SafeRelease(&decoder);
	SafeRelease(&bitmapSource);
	SafeRelease(&converter);

	return bitmap;
}

void Direct2D::DestroyBitmap(ID2D1Bitmap* image)
{
	SafeRelease(&image);
}

void Direct2D::BeginDraw()
{
	_direct2dRenderTarget->BeginDraw();
	_direct2dRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void Direct2D::EndDraw()
{
	_direct2dRenderTarget->EndDraw();
}

void Direct2D::Rotate(D2D1::Matrix3x2F matrix)
{
	_direct2dRenderTarget->SetTransform(matrix);
}

void Direct2D::DrawBitmap(ID2D1Bitmap* _bitmap, D2D1_RECT_F rect, float opacity)
{
	if (!_bitmap) throw L"nullptr Image !";

	D2D1_SIZE_F size = _bitmap->GetSize();
	_direct2dRenderTarget->DrawBitmap(_bitmap, rect, opacity);
}

void Direct2D::DrawTextD(wchar_t* text, IDWriteTextFormat* format, ID2D1Brush* brush)
{
	_direct2dRenderTarget->DrawTextW(text, wcslen(text) + 1, format, D2D1::RectF(0, 0, 400, 400), brush);
}

void Direct2D::DestroyText(IDWriteTextFormat * format, ID2D1Brush * brush)
{
	SafeRelease(&format);
	SafeRelease(&brush);
}

IDWriteTextFormat* Direct2D::CreateTextFormat(char * format, int size)
{
	int length = strlen(format) + 1;
	wchar_t* wFormat = new wchar_t[length];
	mbstowcs_s(0, wFormat, length, format, _TRUNCATE);

	IDWriteFactory* factory = nullptr;
	IDWriteTextFormat* result = nullptr;
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(factory), reinterpret_cast<IUnknown **>(&factory));
	factory->CreateTextFormat(wFormat, nullptr, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", &result);
	result->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	result->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	return result;
}

ID2D1SolidColorBrush * Direct2D::CreateBrush()
{
	ID2D1SolidColorBrush* result = nullptr;
	_direct2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &result);
	return result;
}