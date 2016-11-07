#include "Direct2D.h"
#include <windows.h>
#include <wincodec.h>
#include "GameBitmap.h"
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

Direct::Direct()
{
	_hwnd = NULL;
	_direct2dFactory = NULL;
	_direct2dRenderTarget = NULL;
	_wicFactory = NULL;
}

Direct::~Direct()
{
	SafeRelease(&_direct2dFactory);
	SafeRelease(&_direct2dRenderTarget);
}

Direct* Direct::Instance()
{
	static Direct instance;
	return &instance;
}

HRESULT Direct::CreateDirect2dDevice(HWND hwnd)
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

GameBitmap * Direct::LoadResourceBitmap(int resourceNumber)
{
	return LoadResourceBitmap(MAKEINTRESOURCE(resourceNumber));
}

GameBitmap* Direct::LoadResourceBitmap(PCWSTR resourceName)
{
	ID2D1Bitmap* bitmap = NULL;

	IWICBitmapDecoder *pDecoder = NULL;
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
	ASSERT(hr)

		imageResDataHandle = LoadResource(GetModuleHandle(NULL), imageResHandle);
	hr = imageResDataHandle ? S_OK : E_FAIL;
	ASSERT(hr)

		pImageFile = LockResource(imageResDataHandle);
	hr = pImageFile ? S_OK : E_FAIL;
	ASSERT(hr)

		imageFileSize = SizeofResource(GetModuleHandle(NULL), imageResHandle);
	hr = imageFileSize ? S_OK : E_FAIL;
	ASSERT(hr)

		hr = _wicFactory->CreateStream(&pStream);
	ASSERT(hr)

		hr = pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(pImageFile), imageFileSize);
	ASSERT(hr)

		hr = _wicFactory->CreateDecoderFromStream(pStream, NULL, WICDecodeMetadataCacheOnLoad, &pDecoder);
	ASSERT(hr)

		hr = pDecoder->GetFrame(0, &pSource);
	ASSERT(hr)

		hr = _wicFactory->CreateFormatConverter(&pConverter);
	ASSERT(hr)

		hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
	ASSERT(hr)

		hr = _direct2dRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &bitmap);
	ASSERT(hr)

		SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	return new GameBitmap(bitmap);
}

void Direct::DestroyResourceBitmap(GameBitmap* gameBitmap)
{
	SafeRelease(&(gameBitmap->_bitmap));
	delete gameBitmap;
}

void Direct::BeginLoad()
{
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&_wicFactory);
}

void Direct::EndLoad()
{
	SafeRelease(&_wicFactory);
}

void Direct::BeginDraw()
{
	if (_direct2dRenderTarget == NULL) throw L"NULL RenderTarget !";

	_direct2dRenderTarget->BeginDraw();
	_direct2dRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void Direct::EndDraw()
{
	if (_direct2dRenderTarget == NULL) throw L"NULL RenderTarget !";

	_direct2dRenderTarget->EndDraw();
}

void Direct::Draw(GameBitmap * bitmap)
{
	if (bitmap == NULL) throw L"NULL Image !";
	if (_direct2dRenderTarget == NULL) throw L"NULL RenderTarget !";

	D2D1_SIZE_F size = bitmap->_bitmap->GetSize();
	D2D1_POINT_2F upperLeftCorner = bitmap->_topLeft;
	_direct2dRenderTarget->DrawBitmap(
		bitmap->_bitmap, D2D1::RectF(
			upperLeftCorner.x,
			upperLeftCorner.y,
			upperLeftCorner.x + size.width,
			upperLeftCorner.y + size.height));
}


HRESULT Direct::Test()
{
	HRESULT hr;
	GetClientRect(_hwnd, &_renderArea);
	_direct2dRenderTarget->Resize(D2D1::SizeU(_renderArea.right - _renderArea.left, _renderArea.bottom - _renderArea.top));

	ID2D1SolidColorBrush* pBlackBrush = NULL;
	_direct2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBlackBrush);

	_direct2dRenderTarget->BeginDraw();
	_direct2dRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	_direct2dRenderTarget->FillRectangle(
		D2D1::RectF(
			_renderArea.left + 100.0f,
			_renderArea.top + 100.0f,
			_renderArea.right - 100.0f,
			_renderArea.bottom - 100.0f),
		pBlackBrush);

	hr = _direct2dRenderTarget->EndDraw();
	ASSERT(hr);
	SafeRelease(&pBlackBrush);

	return hr;
}

HRESULT Direct::Test2(int imageId)
{
	BeginLoad();
	GameBitmap* test = LoadResourceBitmap(imageId);
	EndLoad();

	BeginDraw();
	Draw(test);
	EndDraw();

	DestroyResourceBitmap(test);
	return S_OK;
}