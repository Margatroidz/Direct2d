#include "Direct2D.h"
#include <windows.h>
#include <wincodec.h>
#define ASSERT(hr) if(!SUCCEEDED(hr)){ return hr; }

template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

Direct2D::Direct2D() :
	_direct2dFactory(NULL),
	_direct2dRenderTarget(NULL)
{
}

Direct2D::~Direct2D()
{
	SafeRelease(&_direct2dFactory);
	SafeRelease(&_direct2dRenderTarget);
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
	return hr;
}

HRESULT Direct2D::Test()
{
	HRESULT hr;
	GetClientRect(_hwnd, &rectangle);
	_direct2dRenderTarget->Resize(D2D1::SizeU(rectangle.right - rectangle.left, rectangle.bottom - rectangle.top));

	ID2D1SolidColorBrush* pBlackBrush = NULL;
	_direct2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBlackBrush);

	_direct2dRenderTarget->BeginDraw();
	_direct2dRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	_direct2dRenderTarget->FillRectangle(
		D2D1::RectF(
			rectangle.left + 100.0f,
			rectangle.top + 100.0f,
			rectangle.right - 100.0f,
			rectangle.bottom - 100.0f),
		pBlackBrush);

	hr = _direct2dRenderTarget->EndDraw();
	ASSERT(hr);
	SafeRelease(&pBlackBrush);

	return hr;
}

HRESULT Direct2D::Test2(int imageId)
{
	IWICImagingFactory *wicFactory = NULL;
	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory
	);


	ID2D1Bitmap* m_pBitmap = NULL;
	hr = LoadResourceBitmap(
		_direct2dRenderTarget,
		wicFactory,
		MAKEINTRESOURCE(imageId),
		L"Image" ,
		200,
		0,
		&m_pBitmap
	);
	if (m_pBitmap == NULL) MessageBox(NULL, L"test", L"test", MB_OK);
	ASSERT(hr);

	_direct2dRenderTarget->BeginDraw();
	_direct2dRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	D2D1_SIZE_F size = m_pBitmap->GetSize();
	D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(-10.0, -10.0);

	_direct2dRenderTarget->DrawBitmap(
		m_pBitmap, D2D1::RectF(
			upperLeftCorner.x,
			upperLeftCorner.y,
			upperLeftCorner.x + size.width,
			upperLeftCorner.y + size.height));

	

	hr = _direct2dRenderTarget->EndDraw();

	SafeRelease(&wicFactory);
	return S_OK;
}

HRESULT Direct2D::LoadResourceBitmap(
	ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory,
	PCWSTR resourceName,
	PCWSTR resourceType,
	UINT destinationWidth,
	UINT destinationHeight,
	ID2D1Bitmap **ppBitmap)
{
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void *pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResourceW(GetModuleHandle(NULL), resourceName, resourceType);
	HRESULT hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(GetModuleHandle(NULL), imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(GetModuleHandle(NULL), imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;

	}
	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = pIWICFactory->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);

	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);
	return hr;
}
