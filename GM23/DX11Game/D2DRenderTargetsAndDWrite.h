#pragma once

// インクルード
#include <d2d1.h>
#include <dwrite.h>

// lib指定
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

namespace F_lib_Render
{
	class D2DRenderTargetsandDWrite
	{
	public:
		D2DRenderTargetsandDWrite();
		~D2DRenderTargetsandDWrite();

		HRESULT Init(IDXGISwapChain* swapChain, HWND hWnd);

		// getter
		ID2D1Factory*			GetD2DFactory()			const { return D2DFactory; }
		IDWriteFactory*			GetDWriteFactory()		const { return DWriteFactory; }
		ID2D1RenderTarget*		GetDxgiRenderTarget()	const { return DxgiRenderTarget; }
		ID2D1HwndRenderTarget*	GetHwndRenderTarget()	const { return HwndRenderTarget; }
		ID2D1DCRenderTarget*	GetDCRenderTarget()		const { return DCRenderTarget; }

	private:
		HRESULT CreateDeviceIndependentResources();	// デバイス非依存リソースの作成
		HRESULT CreateDeviceResources(IDXGISwapChain* swapChain, HWND hWnd);	// デバイス依存リソースの作成	

		// ヘルパー関数
		HRESULT CreateDxgiRenderTarget(IDXGISwapChain* swapChain);
		HRESULT CreateHwndRenderTarget(HWND hWnd);
		HRESULT CreateDCRenderTarget();

		void DeleteDeviceIndependentResources();	// デバイス非依存リソースの解放
		void DeleteDeviceResources();				// デバイス依存リソースの解放

	private:
		ID2D1Factory*			D2DFactory;			// 2D機能用ファクトリ
		IDWriteFactory*			DWriteFactory;		// Text用ファクトリ
		IDXGISurface*			DXGISurface;
		//ID2D1RenderTarget : Hwnd,DCの基底クラスでもある
		ID2D1RenderTarget*		DxgiRenderTarget;	// DXGI設定でのレンダーターゲット(出力先指定はDXGISurfaceで行う。本当はDXGI用の構成にD3Dと一緒に変更してから使用した方が良いらしい)
		ID2D1HwndRenderTarget*	HwndRenderTarget;	// HWND向け レンダーターゲット
		ID2D1DCRenderTarget*	DCRenderTarget;		// HDC向け レンダーターゲット
		/*レンダーターゲットは出力対象の利用したい描画機能に合わせて選択すること*/
	};
}