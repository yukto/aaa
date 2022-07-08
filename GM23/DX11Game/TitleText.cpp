#include "TitleText.h"
#define TEXTURENAME1		"data/texture/Menu/arena_lv1.png"
#define TEXTURENAME2		"data/texture/Menu/arena_lv2.png"
#define TEXTURENAME3		"data/texture/Menu/arena_lv3.png"
#define TEXTURENAME4		"data/texture/Menu/arena_lv4.png"
#define TEXTURENAME5		"data/texture/Menu/arena_lv5.png"
#define TEXTURENAME6		"data/texture/Menu/arena_lv6.png"
#define TEXTURENAME7		"data/texture/Menu/arena_lv7.png"
#define TEXTURENAME8		"data/texture/Menu/arena_lv8.png"
#define TEXTURENAME9		"data/texture/Menu/arena_lv9.png"
#define TEXTURENAME10		"data/texture/Menu/arena_lv10.png"
static Titletxet ttext[10];

void Titletxet::Update()
{
	for (int i = 0; i < 10; i++)
	{
		ttext[i].g_text.Position.y -= ttext[i].Scroll - gettestnono();
		ttext[i].Scroll = (float)gettestnono();
	}
}

HRESULT InitTitleText()
{
	HRESULT hr;
	hr = ttext[0].InitCText((char*)TEXTURENAME1, XMFLOAT2(212, 28), XMFLOAT3(340.0f, 200.0f, 0));
	hr = ttext[1].InitCText((char*)TEXTURENAME2, XMFLOAT2(212, 28), XMFLOAT3(340.0f, 100.0f, 0));
	hr = ttext[2].InitCText((char*)TEXTURENAME3, XMFLOAT2(212, 28), XMFLOAT3(340.0f, 0.0f, 0));
	hr = ttext[3].InitCText((char*)TEXTURENAME4, XMFLOAT2(212, 28), XMFLOAT3(340.0f, -100.0f, 0));
	hr = ttext[4].InitCText((char*)TEXTURENAME5, XMFLOAT2(212, 28), XMFLOAT3(340.0f, -200.0f, 0));
	hr = ttext[5].InitCText((char*)TEXTURENAME6, XMFLOAT2(212, 28), XMFLOAT3(340.0f, -300.0f, 0));
	hr = ttext[6].InitCText((char*)TEXTURENAME7, XMFLOAT2(212, 28), XMFLOAT3(340.0f, -400.0f, 0));
	hr = ttext[7].InitCText((char*)TEXTURENAME8, XMFLOAT2(212, 28), XMFLOAT3(340.0f, -500.0f, 0));
	hr = ttext[8].InitCText((char*)TEXTURENAME9, XMFLOAT2(212, 28), XMFLOAT3(340.0f, -600.0f, 0));
	hr = ttext[9].InitCText((char*)TEXTURENAME10, XMFLOAT2(212, 28), XMFLOAT3(340.0f, -700.0f, 0));
	return hr;
}

void UninitTitleText()
{
	for (auto&& tx : ttext)
	{
		tx.UninitCText();
	}
}

void UpdateTitleText()
{
	for (auto&& tx:ttext)
	{
		tx.UpdateCText();
		tx.Update();
	}
}

void DrawTitleText(int no)
{
	switch (no)
	{
	case 0:
		for (auto&& tx : ttext)
		{
			tx.DrawCText();
		}
		break;
	default:
		break;
	}
}
