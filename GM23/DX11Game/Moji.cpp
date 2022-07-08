#include "Moji.h"
#include "main.h"
#include <cstdio>
#include <tchar.h>

#pragma warning(disable:4996)

Moji::Moji()
{
	//--------------------------���ǉ���--------------------------
	pD2DFactory = nullptr;
	pDWriteFactory = nullptr;
	pTextFormat = nullptr;
	pRT = nullptr;
	pSolidBrush = nullptr;
	pDXGISurface = nullptr;
	Size = 30;
	//--------------------------���ǉ���--------------------------
}

Moji::~Moji()
{	//--------------------------���ǉ���--------------------------
	if (pDXGISurface) pDXGISurface->Release();
	if (pSolidBrush) pSolidBrush->Release();
	if (pRT) pRT->Release();
	if (pTextFormat) pTextFormat->Release();
	if (pDWriteFactory) pDWriteFactory->Release();
	if (pD2DFactory) pD2DFactory->Release();
	//--------------------------���ǉ���--------------------------

}

HRESULT Moji::Init(IDXGISwapChain * pSwapChain)
{
	HRESULT hr = S_OK;

	//--------------------------���ǉ���--------------------------
	// Direct2D,DirectWrite�̏�����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (FAILED(hr))
		return hr;

	hr = pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pDXGISurface));
	if (FAILED(hr))
		return hr;

	FLOAT dpiX;
	FLOAT dpiY;
	pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);//<-���͐�������Ȃ��L�q(�E�B���h�E��Dpi�擾�֐�)
	//����DisplayInformation�N���X�ɕύX����Ă��邪�A�擾���@��������Ȃ�

	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	hr = pD2DFactory->CreateDxgiSurfaceRenderTarget(pDXGISurface, &props, &pRT);
	if (FAILED(hr))
		return hr;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown * *>(&pDWriteFactory));
	if (FAILED(hr))
		return hr;

	//�֐�CreateTextFormat()
	//��1�����F�t�H���g���iL"���C���I", L"Arial", L"Meiryo UI"���j
	//��2�����F�t�H���g�R���N�V�����inullptr�j
	//��3�����F�t�H���g�̑����iDWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD���j
	//��4�����F�t�H���g�X�^�C���iDWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC�j
	//��5�����F�t�H���g�̕��iDWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED���j
	//��6�����F�t�H���g�T�C�Y�i20, 30���j
	//��7�����F���P�[�����iL""�j
	//��8�����F�e�L�X�g�t�H�[�}�b�g�i&g_pTextFormat�j
	hr = pDWriteFactory->CreateTextFormat(L"���C���I", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, Size, L"", &pTextFormat);
	if (FAILED(hr))
		return hr;

	//�֐�SetTextAlignment()
	//��1�����F�e�L�X�g�̔z�u�iDWRITE_TEXT_ALIGNMENT_LEADING�F�O, DWRITE_TEXT_ALIGNMENT_TRAILING�F��, DWRITE_TEXT_ALIGNMENT_CENTER�F�����j
	hr = pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	if (FAILED(hr))
		return hr;

	//�֐�CreateSolidColorBrush()
	//��1�����F�t�H���g�F�iD2D1::ColorF(D2D1::ColorF::Black)�F��, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))�FRGBA�w��j
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pSolidBrush);
	if (FAILED(hr))
		return hr;

	pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));//�t�H���g�F�ύX�F��

	//--------------------------���ǉ���--------------------------
	return hr;
}

void Moji::Draw(const wchar_t* str, unsigned int str_length, int left, int top, int right, int bottom)
{	//--------------------------���ǉ���--------------------------
	// �e�L�X�g�̕`��
	//WCHAR wcText1[] = L"�@�e����̖��S�C�ŏ����̎����瑹�΂��肵�Ă���B���w�Z�ɋ��鎞���w�Z�̓�K����";
	//WCHAR wcText2[] = L"��э~��Ĉ�T�ԂقǍ��𔲂�������������B�Ȃ�����Ȗ��ł������ƕ����l�����邩";
	//WCHAR wcText3[] = L"���m��ʁB�ʒi�[�����R�ł��Ȃ��B�V�z�̓�K�������o���Ă�����A�������̈�l��";
	//WCHAR wcText4[] = L"��k�ɁA������В����Ă��A���������э~��鎖�͏o���܂��B�㒎��[���B�ƚ�����";
	//WCHAR wcText5[] = L"����ł���B���g�ɕ��Ԃ����ċA���ė������A���₶���傫�Ȋ�����ē�K���炢����";
	//WCHAR wcText6[] = L"��э~��č��𔲂����z�����邩�Ɖ]��������A���̎��͔��������ɔ��Ō����܂���";
	//WCHAR wcText7[] = L"�������B";

	HWND hwnd = FindWindow(_T("AppClass"), _T("Othello�iAI�uAO�v�j"));
	HDC hdc = GetDC(hwnd);

	pRT->BeginDraw();
	//TEXTMETRIC tm;
	//GetTextMetrics(hdc, &tm);
	pRT->DrawText(str, str_length, pTextFormat, D2D1::RectF(left, top, right, bottom), pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	
	pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));//�t�H���g�F�ύX�F��
	//pRT->DrawText(wcText1, ARRAYSIZE(wcText1) - 1, pTextFormat, D2D1::RectF(0, 0, 800, 20), pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	//pRT->DrawText(wcText2, ARRAYSIZE(wcText2) - 1, pTextFormat, D2D1::RectF(0, tm.tmHeight, 800, 40), pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	//pSolidBrush->SetOpacity(0.7f);//�t�H���g�̓����x�ύX�F70��
	//pRT->DrawText(wcText3, ARRAYSIZE(wcText3) - 1, pTextFormat, D2D1::RectF(0, tm.tmHeight * 2, 800, 60), pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	//pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));//�t�H���g�F�ύX�F��
	//pRT->DrawText(wcText4, ARRAYSIZE(wcText4) - 1, pTextFormat, D2D1::RectF(0, tm.tmHeight * 3, 800, 80), pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	//pRT->DrawText(wcText5, ARRAYSIZE(wcText5) - 1, pTextFormat, D2D1::RectF(0, tm.tmHeight * 4, 800, 100), pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	//pSolidBrush->SetOpacity(1.0f);//�t�H���g�̓����x�ύX�F100��
	//pRT->DrawText(wcText6, ARRAYSIZE(wcText6) - 1, pTextFormat, D2D1::RectF(0, tm.tmHeight * 5, 800, 120), pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	//pRT->DrawText(wcText7, ARRAYSIZE(wcText7) - 1, pTextFormat, D2D1::RectF(0, tm.tmHeight * 6, 800, 140), pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	//--------------------------���ǉ���--------------------------
	
	ReleaseDC(hwnd, hdc);
	pRT->EndDraw();
}

void Moji::SetFont(const wchar_t * font_name, int size)
{
	pDWriteFactory->CreateTextFormat(font_name, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &pTextFormat);
}

void Moji::SetBrushColor(float r, float g, float b, float a)
{
	//RGB�ϊ��̏������܂������ĂȂ�
	//pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
	pSolidBrush->SetOpacity(a);
}
