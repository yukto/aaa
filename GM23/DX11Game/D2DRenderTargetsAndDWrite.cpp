#include "D2DRenderTargetsAndDWrite.h"

#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}


//取得方法を変更したのでコメントアウト
//#pragma warning(suppress : 4996)	// GetDesktopDpiの抑制

namespace F_lib_Render
{
	D2DRenderTargetsandDWrite::D2DRenderTargetsandDWrite()
		: D2DFactory(nullptr)
		, DXGISurface(nullptr)
		, DxgiRenderTarget(nullptr)
		, HwndRenderTarget(nullptr)
		, DCRenderTarget(nullptr)
	{
	}

	D2DRenderTargetsandDWrite::~D2DRenderTargetsandDWrite()
	{
		DeleteDeviceIndependentResources();
		DeleteDeviceResources();
	}

	HRESULT D2DRenderTargetsandDWrite::Init(IDXGISwapChain* swapChain, HWND hWnd)
	{
		HRESULT hr = S_OK;
		hr = CreateDeviceIndependentResources();
		if (FAILED(hr)) return hr;
		hr = CreateDeviceResources(swapChain, hWnd);
		if (FAILED(hr))	return hr;

		return hr;
	}
#pragma region CreateResources
	HRESULT D2DRenderTargetsandDWrite::CreateDeviceIndependentResources()
	{
		HRESULT hr = S_OK;
		// D2Dファクトリの作成
		hr = ::D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,	// 使用スレッドの指定
			IID_ID2D1Factory,					// インターフェースIDの指定
			(void**)&D2DFactory					// 出力ポインタ
		);
		if (FAILED(hr))
			return hr;

		// DWriteの作成
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,			// ファクトリタイプの指定
			__uuidof(IDWriteFactory),			// インターフェースIDの指定
			reinterpret_cast<IUnknown * *>(&DWriteFactory)	// 出力ポインタ
		);
		if (FAILED(hr))
			return hr;

		return hr;
	}

	HRESULT D2DRenderTargetsandDWrite::CreateDeviceResources(IDXGISwapChain* swapChain, HWND hWnd)
	{
		HRESULT hr = S_OK;
		if (D2DFactory == nullptr) {	// ファクトリが無ければなにもしない
			return E_FAIL;
		}

		//　レンダーターゲットの作成
		hr = CreateDxgiRenderTarget(swapChain);
		hr = CreateHwndRenderTarget(hWnd);
		hr = CreateDCRenderTarget();

		return hr;
	}

	HRESULT D2DRenderTargetsandDWrite::CreateDxgiRenderTarget(IDXGISwapChain* swapChain)
	{
		HRESULT hr;
		//　DXGIを利用したレンダーターゲットの作成
		if (DxgiRenderTarget == nullptr) {
			hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&DXGISurface));	// SwapChainから使用バッファを取得
			if (FAILED(hr))
				return hr;

			//FLOAT dpiX;
			//FLOAT dpiY;
			//D2DFactory->GetDesktopDpi(&dpiX, &dpiY);//<-今は推奨されない記述(ウィンドウのDpi取得関数)
			////今はDisplayInformationクラスに変更されているが、取得方法が分からない

			//下記の取得方に変更
			HDC hdc = GetDC(NULL);
			FLOAT dpiX = (FLOAT)GetDeviceCaps(hdc, LOGPIXELSX);
			FLOAT dpiY = (FLOAT)GetDeviceCaps(hdc, LOGPIXELSY);
			ReleaseDC(NULL, hdc);

			// プロパティパラメータを作成
			D2D1_RENDER_TARGET_PROPERTIES props =
				D2D1::RenderTargetProperties(
					D2D1_RENDER_TARGET_TYPE_DEFAULT,
					D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
					dpiX, dpiY);

			hr = D2DFactory->CreateDxgiSurfaceRenderTarget(DXGISurface, &props, &DxgiRenderTarget);
			if (FAILED(hr))
				return hr;

			// アンチエイリアシングモード
			DxgiRenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
		}
		return hr;
	}

	HRESULT D2DRenderTargetsandDWrite::CreateHwndRenderTarget(HWND hWnd)
	{
		HRESULT hr;
		// Hwndを指定したレンダーターゲットの作成
		if (HwndRenderTarget == nullptr) {
			RECT rect;
			::GetClientRect(hWnd, &rect);
			D2D1_SIZE_U size = D2D1::Size<UINT>(rect.right - rect.left, rect.bottom - rect.top);
			hr = D2DFactory->CreateHwndRenderTarget( // ヘルパー関数を利用して作成
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(hWnd, size),
				&HwndRenderTarget);
			if (FAILED(hr))
				return hr;
		}
		return hr;
	}

	HRESULT D2DRenderTargetsandDWrite::CreateDCRenderTarget()
	{
		HRESULT hr;
		// DC互換のレンダーターゲットの作成
		if (DCRenderTarget == nullptr) {
			// プロパティパラメータを作成
			D2D1_RENDER_TARGET_PROPERTIES props =
				D2D1::RenderTargetProperties(
					D2D1_RENDER_TARGET_TYPE_DEFAULT,
					D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
					0.0F, 0.0F,
					D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE
				);
			hr = D2DFactory->CreateDCRenderTarget(&props, &DCRenderTarget);
			if (FAILED(hr))
				return hr;
		}
		return hr;
	}
#pragma endregion CreateResources


#pragma region DeleteResources
	void D2DRenderTargetsandDWrite::DeleteDeviceIndependentResources()
	{
		SAFE_RELEASE(D2DFactory);
		SAFE_RELEASE(DWriteFactory);
	}

	void D2DRenderTargetsandDWrite::DeleteDeviceResources()
	{
		SAFE_RELEASE(DXGISurface);
		SAFE_RELEASE(DxgiRenderTarget);
		SAFE_RELEASE(HwndRenderTarget);
		SAFE_RELEASE(DCRenderTarget);
	}
#pragma endregion DeleteResources
}
