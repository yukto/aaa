#pragma once
#pragma comment(lib,"d2d1.lib")//---���ǉ�---
#pragma comment(lib,"dwrite.lib")//---���ǉ�---
#include <directxcolors.h>//---���ǉ�---
#include <d2d1.h>//---���ǉ�---
#include <dwrite.h>//---���ǉ�---

class Moji
{
public:
	Moji();
	~Moji();

	HRESULT Init(IDXGISwapChain* pSwapChain);
	void Draw(const wchar_t* str, unsigned int str_length, int left, int top, int right, int bottom);
	void SetFont(const wchar_t* font_name, int size);
	void SetBrushColor(float r, float g, float b, float a);
private:
	//--------------------------���ǉ���--------------------------
	ID2D1Factory* pD2DFactory;	//2D�\���̏�����
	IDWriteFactory* pDWriteFactory;	//�����\���̏�����
	IDWriteTextFormat* pTextFormat;	//�t�H���g���
	ID2D1RenderTarget* pRT;	//Draw�֌W
	ID2D1SolidColorBrush* pSolidBrush;	//�u���V���
	IDXGISurface* pDXGISurface;	//�`���2D�֕ϊ�
	int		Size;
	//--------------------------���ǉ���--------------------------
};

