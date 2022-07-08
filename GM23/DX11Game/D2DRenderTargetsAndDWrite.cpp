#include "D2DRenderTargetsAndDWrite.h"

#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}


//�擾���@��ύX�����̂ŃR�����g�A�E�g
//#pragma warning(suppress : 4996)	// GetDesktopDpi�̗}��

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
		// D2D�t�@�N�g���̍쐬
		hr = ::D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,	// �g�p�X���b�h�̎w��
			IID_ID2D1Factory,					// �C���^�[�t�F�[�XID�̎w��
			(void**)&D2DFactory					// �o�̓|�C���^
		);
		if (FAILED(hr))
			return hr;

		// DWrite�̍쐬
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,			// �t�@�N�g���^�C�v�̎w��
			__uuidof(IDWriteFactory),			// �C���^�[�t�F�[�XID�̎w��
			reinterpret_cast<IUnknown * *>(&DWriteFactory)	// �o�̓|�C���^
		);
		if (FAILED(hr))
			return hr;

		return hr;
	}

	HRESULT D2DRenderTargetsandDWrite::CreateDeviceResources(IDXGISwapChain* swapChain, HWND hWnd)
	{
		HRESULT hr = S_OK;
		if (D2DFactory == nullptr) {	// �t�@�N�g����������΂Ȃɂ����Ȃ�
			return E_FAIL;
		}

		//�@�����_�[�^�[�Q�b�g�̍쐬
		hr = CreateDxgiRenderTarget(swapChain);
		hr = CreateHwndRenderTarget(hWnd);
		hr = CreateDCRenderTarget();

		return hr;
	}

	HRESULT D2DRenderTargetsandDWrite::CreateDxgiRenderTarget(IDXGISwapChain* swapChain)
	{
		HRESULT hr;
		//�@DXGI�𗘗p���������_�[�^�[�Q�b�g�̍쐬
		if (DxgiRenderTarget == nullptr) {
			hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&DXGISurface));	// SwapChain����g�p�o�b�t�@���擾
			if (FAILED(hr))
				return hr;

			//FLOAT dpiX;
			//FLOAT dpiY;
			//D2DFactory->GetDesktopDpi(&dpiX, &dpiY);//<-���͐�������Ȃ��L�q(�E�B���h�E��Dpi�擾�֐�)
			////����DisplayInformation�N���X�ɕύX����Ă��邪�A�擾���@��������Ȃ�

			//���L�̎擾���ɕύX
			HDC hdc = GetDC(NULL);
			FLOAT dpiX = (FLOAT)GetDeviceCaps(hdc, LOGPIXELSX);
			FLOAT dpiY = (FLOAT)GetDeviceCaps(hdc, LOGPIXELSY);
			ReleaseDC(NULL, hdc);

			// �v���p�e�B�p�����[�^���쐬
			D2D1_RENDER_TARGET_PROPERTIES props =
				D2D1::RenderTargetProperties(
					D2D1_RENDER_TARGET_TYPE_DEFAULT,
					D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
					dpiX, dpiY);

			hr = D2DFactory->CreateDxgiSurfaceRenderTarget(DXGISurface, &props, &DxgiRenderTarget);
			if (FAILED(hr))
				return hr;

			// �A���`�G�C���A�V���O���[�h
			DxgiRenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
		}
		return hr;
	}

	HRESULT D2DRenderTargetsandDWrite::CreateHwndRenderTarget(HWND hWnd)
	{
		HRESULT hr;
		// Hwnd���w�肵�������_�[�^�[�Q�b�g�̍쐬
		if (HwndRenderTarget == nullptr) {
			RECT rect;
			::GetClientRect(hWnd, &rect);
			D2D1_SIZE_U size = D2D1::Size<UINT>(rect.right - rect.left, rect.bottom - rect.top);
			hr = D2DFactory->CreateHwndRenderTarget( // �w���p�[�֐��𗘗p���č쐬
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
		// DC�݊��̃����_�[�^�[�Q�b�g�̍쐬
		if (DCRenderTarget == nullptr) {
			// �v���p�e�B�p�����[�^���쐬
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
