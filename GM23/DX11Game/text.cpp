//=============================================================================
//
// プレイヤー [Text.cpp]
// Author : SHOUEI HIRAMATSU 
//
//------------------------------------
//開発履歴:2021/06/23 作成開始:
//				06/** ******機能の実装
//=============================================================================

//メニュー画面
#ifdef _DEBUG
#include "debugproc.h"
#endif // _DEBUG

//******インクルード******
#include"text.h"
#include"Texture.h"
#include "polygon.h"
#include"main.h"
#include"collision.h"
#include <time.h>
#include "sceneTitle.h"

//******定数宣言******
#define TEXTNAME1	_T("data/texture/HS/ホーム.png")
#define TEXTNAME2	_T("data/texture/HS/バトル.png")
#define TEXTNAME3	_T("data/texture/HS/トレーニング.png")
#define TEXTNAME4	_T("data/texture/クローズ1.png")
#define TEXTNAME5	_T("data/texture/クローズ1.png")
#define TEXTNAME6	_T("data/texture/クローズ1.png")
#define TEXTNAME7	_T("data/texture/クローズ2.png")
#define TEXTNAME8	_T("data/texture/タイトルへ戻る.png")
#define TEXTNAME9	_T("data/texture/闘技場A.png")
#define TEXTNAME10	_T("data/texture/闘技場B.png")
#define TEXTNAME11	_T("data/texture/闘技場C.png")
#define TEXTNAME12	_T("data/texture/闘技場C.png")
#define TEXTNAME13	_T("data/texture/闘技場C.png")
#define TEXTNAME14	_T("data/texture/闘技場C.png")
#define TEXTNAME15	_T("data/texture/闘技場C.png")
#define TEXTNAME16	_T("data/texture/闘技場C.png")
#define TEXTNAME17	_T("data/texture/闘技場C.png")
#define TEXTNAME18	_T("data/texture/闘技場C.png")
#define TEXTNAME19	_T("data/texture/闘技場C.png")
#define TEXTNAME20	_T("data/texture/闘技場C.png")
#define TEXTNAME21	_T("data/texture/闘技場C.png")
#define TEXT_NO		(21)

#define NO0	_T("data/texture/No/No10.png")
#define NO1	_T("data/texture/No/No01.png")
#define NO2	_T("data/texture/No/No02.png")
#define NO3	_T("data/texture/No/No03.png")
#define NO4	_T("data/texture/No/No04.png")
#define NO5	_T("data/texture/No/No05.png")
#define NO6	_T("data/texture/No/No06.png")
#define NO7	_T("data/texture/No/No07.png")
#define NO8	_T("data/texture/No/No08.png")
#define NO9	_T("data/texture/No/No09.png")
#define N10	_T("data/texture/No/No09.png")
#define NO_NO				(11)

//******グローバル変数******
static TEXT_2D	textno[TEXT_NO];
static TEXT_2D	No[NO_NO];
static float	MenuPos;

// 初期化//=============================================================================
//=============================================================================
HRESULT InitText()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	//テクスチャ
	hr = CreateTextureFromFile(pDevice, TEXTNAME1, &textno[0].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME2, &textno[1].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME3, &textno[2].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME1, &textno[3].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME1, &textno[4].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME6, &textno[5].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME7, &textno[6].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME8, &textno[7].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME9, &textno[8].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME10, &textno[9].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME11, &textno[10].g_pTexture);

	hr = CreateTextureFromFile(pDevice, TEXTNAME12, &textno[11].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME13, &textno[12].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME11, &textno[13].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME11, &textno[14].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME16, &textno[15].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME17, &textno[16].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME18, &textno[17].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME19, &textno[18].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME20, &textno[19].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME21, &textno[20].g_pTexture);
	hr = CreateTextureFromFile(pDevice, NO0, &No[0].g_pTexture);
	hr = CreateTextureFromFile(pDevice, NO1, &No[1].g_pTexture);
	hr = CreateTextureFromFile(pDevice, NO2, &No[2].g_pTexture);
	hr = CreateTextureFromFile(pDevice, NO3, &No[3].g_pTexture);
	hr = CreateTextureFromFile(pDevice, NO4, &No[4].g_pTexture);
	hr = CreateTextureFromFile(pDevice, NO5, &No[5].g_pTexture);
	hr = CreateTextureFromFile(pDevice, NO6, &No[6].g_pTexture);
	hr = CreateTextureFromFile(pDevice, NO7, &No[7].g_pTexture);
	hr = CreateTextureFromFile(pDevice, NO8, &No[8].g_pTexture);
	hr = CreateTextureFromFile(pDevice, NO9, &No[9].g_pTexture);
	hr = CreateTextureFromFile(pDevice, N10, &No[10].g_pTexture);
	for (int i = 0; i < TEXT_NO; i++)
	{
		textno[i].g_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		textno[i].g_Size = XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
		textno[i].g_Angle = 0.0f;
		textno[i].g_vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		textno[i].g_Scale = XMFLOAT2(1.0f, 1.0f);
		textno[i].g_TexCoord = XMFLOAT2(1.0f, 1.0f);
		textno[i].g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
		textno[i].Alfa = 1.0f;
		textno[i].AlfaAd = 0.0f;
	}
	for (int i = 0; i < NO_NO; i++)
	{
		No[i].g_Size = XMFLOAT2(39, 69);
		No[i].g_Angle = 0.0f;
		No[i].g_vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		No[i].g_Scale = XMFLOAT2(1.0f, 1.0f);
		No[i].g_TexCoord = XMFLOAT2(220.0f, 220.0f);
		No[i].g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
		No[i].g_Position = XMFLOAT3(520, -275, 0.0f);
	}
	textno[0].g_Position = XMFLOAT3(0.0f, -310.0f, 0.0f);
	textno[1].g_Position = XMFLOAT3(200.0f, -310.0f, 0.0f);
	textno[2].g_Position = XMFLOAT3(-200.0f, -310.0f, 0.0f);
	textno[3].g_Position = XMFLOAT3(-500.0f, -310.0f, 0.0f);
	textno[4].g_Position = XMFLOAT3(500.0f, -310.0f, 0.0f);
	textno[5].g_Position = XMFLOAT3(0.0f, -210.0f, 0.0f);
	textno[5].g_Size = XMFLOAT2(SCREEN_WIDTH, 300);
	textno[6].g_Position = XMFLOAT3(520.0f, -123.0f, 0.0f);
	textno[6].g_Size = XMFLOAT2(240, 127);
	textno[7].g_Position = XMFLOAT3(-560.0f, 332.0f, 0.0f);
	textno[7].g_Size = XMFLOAT2(160, 77);
	textno[8].g_Position = XMFLOAT3(340.0f, 200.0f, 0.0f);
	textno[8].g_Size = XMFLOAT2(297, 145);
	textno[9].g_Position = XMFLOAT3(340.0f, 50.0f, 0.0f);
	textno[9].g_Size = XMFLOAT2(297, 145);
	textno[10].g_Position = XMFLOAT3(340.0f, -100.0f, 0.0f);
	textno[10].g_Size = XMFLOAT2(297, 145);
	for (int i = 0; i < 5; i++)
	{
		textno[i].g_Size = XMFLOAT2(100, 100);
		textno[i].Alfa = 0.5f;
		textno[i].g_vel = XMFLOAT3(((float)((rand() % 200) - 100) * 0.01f), ((float)((rand() % 200) - 100) * 0.01f), 0.0f);
	}
	for (int i = 11; i < 21; i++)
	{
		textno[i].g_Size = XMFLOAT2(266, 35);
		textno[i].g_Position = XMFLOAT3(340.0f, 200.0f - ((i - 11) * 100), 0.0f);
	}
	MenuPos = 0.0f;
	return hr;
}


//=============================================================================
// 終了
//=============================================================================
void UninitText()
{
	for (int i = 0; i < TEXT_NO; i++)
	{
		SAFE_RELEASE(textno[i].g_pTexture);
	}
	for (int i = 0; i < NO_NO; i++)
	{
		SAFE_RELEASE(No[i].g_pTexture);
	}
}

//=============================================================================
// 更新
//=============================================================================
void UpdateText()
{
	for (int i = 0; i < TEXT_NO; i++)
	{
		if (GetMenuSwitch() != 0)continue;
		textno[i].g_Position.x += textno[i].g_vel.x;
		textno[i].g_Position.y += textno[i].g_vel.y;
		if (abs(textno[i].g_Position.x) > SCREEN_WIDTH / 2 - textno[i].g_Size.x / 2)textno[i].g_vel.x *= -1.0f;
		if (abs(textno[i].g_Position.y + 285.0f) > 150.0f / 2 - textno[i].g_Size.y / 2)textno[i].g_vel.y *= -1.0f;
		for (int a = 0; a < 5; a++)
		{
			if (a <= i)continue;
			if (abs(textno[i].g_Position.x - textno[a].g_Position.x) <= 100 &&
				abs(textno[i].g_Position.y - textno[a].g_Position.y) <= 100 && 
				(abs(textno[i].g_Position.x - textno[a].g_Position.x) * abs(textno[i].g_Position.x - textno[a].g_Position.x) +
					abs(textno[i].g_Position.y - textno[a].g_Position.y) * abs(textno[i].g_Position.y - textno[a].g_Position.y) <= 10000))
			{
				XMFLOAT2 v1New, v2New;
				v1New.x = textno[a].g_vel.x;
				v2New.x = textno[i].g_vel.x;
				v1New.y = textno[a].g_vel.y;
				v2New.y = textno[i].g_vel.y;
				textno[i].g_vel.x = v1New.x;
				textno[a].g_vel.x = v2New.x;
				textno[i].g_vel.y = v1New.y;
				textno[a].g_vel.y = v2New.y;
			}
		}
		textno[i].Alfa += textno[i].AlfaAd;
		if (textno[i].Alfa >= 1.0f)textno[i].Alfa = 1.0f;
		if (textno[i].Alfa <= 0.0f)textno[i].Alfa = 0.0f;
		if (textno[i].Alfa >= 1.0f || textno[i].Alfa <= 0.0f)textno[i].AlfaAd = -textno[i].AlfaAd;
	}
}

//=============================================================================
// 描画
//=============================================================================
void Draw_Text(int i)
{
	SetPolygonAlpha(textno[i].Alfa);
	//ポリゴンの情報設定
	if(i >= 0 && i <= 6)SetPolygonPos(textno[i].g_Position.x, textno[i].g_Position.y + MenuPos); 
	else if (i >= 8 && i <= 10)SetPolygonPos(textno[i].g_Position.x, textno[i].g_Position.y + gettestnono());
	else SetPolygonPos(textno[i].g_Position.x, textno[i].g_Position.y);
	SetPolygonSize(textno[i].g_Size.x, textno[i].g_Size.y);
	if (i < 11)
	{
		if (HS_TitleMouseCollision(0) == i || GetMenuNo() - 1 == i)
		{
			SetPolygonAlpha(1.0f);
			SetPolygonSize(textno[i].g_Size.x * 1.3f, textno[i].g_Size.y * 1.3f);
		}
	}
	SetPolygonAngle(textno[i].g_Angle);
	//degree(デグリー)値
	SetPolygonUV(textno[i].g_TexCoord.x, textno[i].g_TexCoord.y);		  //左上のUV座標
	SetPolygonFrameSize(textno[i].g_TexFrameSize.x, textno[i].g_TexFrameSize.y);  //横幅縦幅
	SetPolygonTexture(textno[i].g_pTexture);	  //テクスチャ指定

	// ポリゴンの描画処理
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	SetPolygonAlpha(1.0f);
	SetPolygonColor(1.0f, 1.0f, 1.0f);
}

void Draw_TextAll(int i, XMFLOAT2 pos,XMFLOAT2 size)
{
	SetPolygonAlpha(textno[i].Alfa);
	//ポリゴンの情報設定
	SetPolygonPos(pos.x, pos.y);
	SetPolygonSize(size.x, size.y);
	SetPolygonAngle(textno[i].g_Angle);
	//degree(デグリー)値
	SetPolygonUV(textno[i].g_TexCoord.x, textno[i].g_TexCoord.y);		  //左上のUV座標
	SetPolygonFrameSize(textno[i].g_TexFrameSize.x, textno[i].g_TexFrameSize.y);  //横幅縦幅
	SetPolygonTexture(textno[i].g_pTexture);	  //テクスチャ指定

	// ポリゴンの描画処理
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	SetPolygonAlpha(1.0f);
}

void Draw_CompleteNo(int i, XMFLOAT2 pos, float sc)
{
	static int MAXno = 999999;
	static int MINno = -99999;
	int Digits, INo, DNo[6];
	INo = i;
	Digits = 0;
	if (i > MAXno)INo = MAXno;
	if (i < 0)
	{
		if (i < MINno)INo = MINno;
		INo = INo * -1;
		DNo[5] = 10;
	}
	do {
		DNo[Digits] = INo % 10;
		INo = INo / 10;
		Digits++;
	} while (INo != 0);
	for (int i = 0; i < Digits; i++)
	{
		//ポリゴンの情報設定
		SetPolygonPos(pos.x - (float)(39 * sc*i), pos.y);
		SetPolygonSize(No[DNo[i]].g_Size.x*sc, No[DNo[i]].g_Size.y*sc);
		SetPolygonAngle(No[DNo[i]].g_Angle);
		//degree(デグリー)値
		SetPolygonUV(No[DNo[i]].g_TexCoord.x, No[DNo[i]].g_TexCoord.y);		  //左上のUV座標
		SetPolygonFrameSize(No[DNo[i]].g_TexFrameSize.x, No[DNo[i]].g_TexFrameSize.y);  //横幅縦幅
		SetPolygonTexture(No[DNo[i]].g_pTexture);	  //テクスチャ指定

		// ポリゴンの描画処理
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
		DrawPolygon(pDeviceContext);
	}
}

TEXT_2D GetTextData(int no)
{
	return textno[no];
}

void MenuPosAdo(float pos)
{
	MenuPos += pos;
	if (MenuPos <= -190.0f)SetMenuSwitch(3);
	if(MenuPos >= 0.0f)SetMenuSwitch(0);
}

float GetMenuPos()
{
	return MenuPos;
}