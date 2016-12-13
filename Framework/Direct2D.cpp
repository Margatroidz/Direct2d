#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "windowscodecs")
#include "Direct2D.h"
#include <windows.h>
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
}

Direct2D* Direct2D::Instance()
{
	static Direct2D instance;
	return &instance;
}

HRESULT Direct2D::CreateDirect2dDevice(HWND hwnd)
{
	_hwnd = hwnd;
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_direct2dFactory);
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

ID2D1Bitmap* Direct2D::LoadBitmap(int resourceNumber)
{
	return LoadBitmap(MAKEINTRESOURCE(resourceNumber));
}

ID2D1Bitmap* Direct2D::LoadBitmap(char* resourceName)
{
	return LoadBitmap((WCHAR*)resourceName);;
}

void Direct2D::DestroyBitmap(ID2D1Bitmap* image)
{
	SafeRelease(&image);
}

void Direct2D::BeginLoad()
{
	CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&_wicFactory);
}

void Direct2D::EndLoad()
{
	SafeRelease(&_wicFactory);
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

void Direct2D::DrawTextD(char* text, IDWriteTextFormat* format, ID2D1Brush* brush)
{
	int length = strlen(text);
	wchar_t* t = new wchar_t[length];
	mbstowcs_s(0, t, length, text, _TRUNCATE);
	_direct2dRenderTarget->DrawTextW(t, length, format, D2D1::RectF(200, 200, 400, 400), brush);
	delete[] t;
}

void Direct2D::Test()
{
	static const WCHAR msc_fontName[] = L"Gabriola";
	static const FLOAT msc_fontSize = 50;
	IDWriteFactory* m_pDWriteFactory = NULL;
	IDWriteTextFormat* m_pTextFormat;

	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pDWriteFactory),
		reinterpret_cast<IUnknown **>(&m_pDWriteFactory)
	);
	m_pDWriteFactory->CreateTextFormat(
		msc_fontName,
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		msc_fontSize,
		L"en-us",
		&m_pTextFormat
	);
	m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	ID2D1SolidColorBrush* brush = nullptr;

	_direct2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &brush);

	DrawTextD("Hello Horld !", m_pTextFormat, brush);

	SafeRelease(&m_pDWriteFactory);
	SafeRelease(&m_pTextFormat);
	SafeRelease(&brush);
}

ID2D1Bitmap* Direct2D::LoadBitmap(PCWSTR resourceName)
{
	ID2D1Bitmap* bitmap = nullptr;
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode *pSource = nullptr;
	IWICStream *pStream = nullptr;
	IWICFormatConverter *pConverter = nullptr;


	// Locate the resource.
	HRSRC imageResHandle = FindResourceW(GetModuleHandle(nullptr), resourceName, L"Image");
	ASSERT(imageResHandle ? S_OK : E_FAIL);

	HGLOBAL imageResDataHandle = LoadResource(GetModuleHandle(nullptr), imageResHandle);
	ASSERT(imageResDataHandle ? S_OK : E_FAIL);

	void *pImageFile = LockResource(imageResDataHandle);
	ASSERT(pImageFile ? S_OK : E_FAIL);

	DWORD imageFileSize = SizeofResource(GetModuleHandle(nullptr), imageResHandle);
	ASSERT(imageFileSize ? S_OK : E_FAIL);

	ASSERT(_wicFactory->CreateStream(&pStream));
	ASSERT(pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(pImageFile), imageFileSize));
	ASSERT(_wicFactory->CreateDecoderFromStream(pStream, nullptr, WICDecodeMetadataCacheOnLoad, &pDecoder));
	ASSERT(pDecoder->GetFrame(0, &pSource));
	ASSERT(_wicFactory->CreateFormatConverter(&pConverter));
	ASSERT(pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeMedianCut));
	ASSERT(_direct2dRenderTarget->CreateBitmapFromWicBitmap(pConverter, nullptr, &bitmap));

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	return bitmap;
}