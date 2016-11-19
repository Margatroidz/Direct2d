#pragma comment(lib, "d2d1")
#pragma comment(lib, "windowscodecs")
#include "Direct2D.h"
#include <windows.h>
#include <wincodec.h>
#include <memory>
#include "Image.h"
#define ASSERT(hr) if(!SUCCEEDED(hr)){ throw hr; }

template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

Direct2D::Direct2D()
{
	_hwnd = NULL;
	_direct2dFactory = NULL;
	_direct2dRenderTarget = NULL;
	_wicFactory = NULL;
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
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&_wicFactory);
}

void Direct2D::EndLoad()
{
	SafeRelease(&_wicFactory);
}

void Direct2D::BeginDraw()
{
	if (_direct2dRenderTarget == NULL) throw L"NULL RenderTarget !";

	_direct2dRenderTarget->BeginDraw();
	_direct2dRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void Direct2D::EndDraw()
{
	if (_direct2dRenderTarget == NULL) throw L"NULL RenderTarget !";

	_direct2dRenderTarget->EndDraw();
}

void Direct2D::Draw(ID2D1Bitmap* _bitmap, float _topLeftX, float _topLeftY)
{
	if (!_bitmap) throw L"NULL Image !";
	if (!_direct2dRenderTarget) throw L"NULL RenderTarget !";

	D2D1_SIZE_F size = _bitmap->GetSize();
	_direct2dRenderTarget->DrawBitmap(
			_bitmap, D2D1::RectF(
			_topLeftX,
			_topLeftY,
			_topLeftX + size.width,
			_topLeftY + size.height));
}

ID2D1Bitmap* Direct2D::LoadBitmap(PCWSTR resourceName)
{
	ID2D1Bitmap* bitmap = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void *pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResourceW(GetModuleHandle(NULL), resourceName, L"Image");
	HRESULT hr = imageResHandle ? S_OK : E_FAIL;
	ASSERT(hr);
	imageResDataHandle = LoadResource(GetModuleHandle(NULL), imageResHandle);
	hr = imageResDataHandle ? S_OK : E_FAIL;
	ASSERT(hr);
	pImageFile = LockResource(imageResDataHandle);
	hr = pImageFile ? S_OK : E_FAIL;
	ASSERT(hr);
	imageFileSize = SizeofResource(GetModuleHandle(NULL), imageResHandle);
	hr = imageFileSize ? S_OK : E_FAIL;
	ASSERT(hr);
	hr = _wicFactory->CreateStream(&pStream);
	ASSERT(hr);
	hr = pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(pImageFile), imageFileSize);
	ASSERT(hr);
	hr = _wicFactory->CreateDecoderFromStream(pStream, NULL, WICDecodeMetadataCacheOnLoad, &pDecoder);
	ASSERT(hr);
	hr = pDecoder->GetFrame(0, &pSource);
	ASSERT(hr);
	hr = _wicFactory->CreateFormatConverter(&pConverter);
	ASSERT(hr);
	hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
	ASSERT(hr);
	hr = _direct2dRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &bitmap);
	ASSERT(hr);

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	return bitmap;
}