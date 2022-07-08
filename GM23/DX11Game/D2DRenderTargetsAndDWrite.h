#pragma once

// �C���N���[�h
#include <d2d1.h>
#include <dwrite.h>

// lib�w��
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
		HRESULT CreateDeviceIndependentResources();	// �f�o�C�X��ˑ����\�[�X�̍쐬
		HRESULT CreateDeviceResources(IDXGISwapChain* swapChain, HWND hWnd);	// �f�o�C�X�ˑ����\�[�X�̍쐬	

		// �w���p�[�֐�
		HRESULT CreateDxgiRenderTarget(IDXGISwapChain* swapChain);
		HRESULT CreateHwndRenderTarget(HWND hWnd);
		HRESULT CreateDCRenderTarget();

		void DeleteDeviceIndependentResources();	// �f�o�C�X��ˑ����\�[�X�̉��
		void DeleteDeviceResources();				// �f�o�C�X�ˑ����\�[�X�̉��

	private:
		ID2D1Factory*			D2DFactory;			// 2D�@�\�p�t�@�N�g��
		IDWriteFactory*			DWriteFactory;		// Text�p�t�@�N�g��
		IDXGISurface*			DXGISurface;
		//ID2D1RenderTarget : Hwnd,DC�̊��N���X�ł�����
		ID2D1RenderTarget*		DxgiRenderTarget;	// DXGI�ݒ�ł̃����_�[�^�[�Q�b�g(�o�͐�w���DXGISurface�ōs���B�{����DXGI�p�̍\����D3D�ƈꏏ�ɕύX���Ă���g�p���������ǂ��炵��)
		ID2D1HwndRenderTarget*	HwndRenderTarget;	// HWND���� �����_�[�^�[�Q�b�g
		ID2D1DCRenderTarget*	DCRenderTarget;		// HDC���� �����_�[�^�[�Q�b�g
		/*�����_�[�^�[�Q�b�g�͏o�͑Ώۂ̗��p�������`��@�\�ɍ��킹�đI�����邱��*/
	};
}