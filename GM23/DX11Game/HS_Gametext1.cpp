//=============================================================================
//
// プレイヤー [HS_Gametext1.cpp]
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
#include"HS_Gametext1.h"
#include"Texture.h"
#include "polygon.h"
#include"main.h"

//******定数宣言******
#define TEXTNAME1	_T("data/texture/HS/moji/0.png")
#define TEXTNAME2	_T("data/texture/HS/moji/1.png")
#define TEXTNAME3	_T("data/texture/HS/moji/2.png")
#define TEXTNAME4	_T("data/texture/HS/moji/3.png")
#define TEXTNAME5	_T("data/texture/HS/moji/4.png")
#define TEXTNAME6	_T("data/texture/HS/moji/5.png")
#define TEXTNAME7	_T("data/texture/HS/moji/6.png")
#define TEXTNAME8	_T("data/texture/HS/moji/7.png")
#define TEXTNAME9	_T("data/texture/HS/moji/8.png")
#define TEXTNAME10	_T("data/texture/HS/moji/9.png")
#define TEXTNAME11	_T("data/texture/HS/moji/a.png")
#define TEXTNAME12	_T("data/texture/HS/moji/b.png")
#define TEXTNAME13	_T("data/texture/HS/moji/c.png")
#define TEXTNAME14	_T("data/texture/HS/moji/d.png")
#define TEXTNAME15	_T("data/texture/HS/moji/e.png")
#define TEXTNAME16	_T("data/texture/HS/moji/f.png")
#define TEXTNAME17	_T("data/texture/HS/moji/g.png")
#define TEXTNAME18	_T("data/texture/HS/moji/h.png")
#define TEXTNAME19	_T("data/texture/HS/moji/i.png")
#define TEXTNAME20	_T("data/texture/HS/moji/j.png")
#define TEXTNAME21	_T("data/texture/HS/moji/k.png")
#define TEXTNAME22	_T("data/texture/HS/moji/l.png")
#define TEXTNAME23	_T("data/texture/HS/moji/m.png")
#define TEXTNAME24	_T("data/texture/HS/moji/n.png")
#define TEXTNAME25	_T("data/texture/HS/moji/o.png")
#define TEXTNAME26	_T("data/texture/HS/moji/p.png")
#define TEXTNAME27	_T("data/texture/HS/moji/q.png")
#define TEXTNAME28	_T("data/texture/HS/moji/r.png")
#define TEXTNAME29	_T("data/texture/HS/moji/s.png")
#define TEXTNAME30	_T("data/texture/HS/moji/t.png")
#define TEXTNAME31	_T("data/texture/HS/moji/u.png")
#define TEXTNAME32	_T("data/texture/HS/moji/v.png")
#define TEXTNAME33	_T("data/texture/HS/moji/w.png")
#define TEXTNAME34	_T("data/texture/HS/moji/x.png")
#define TEXTNAME35	_T("data/texture/HS/moji/y.png")
#define TEXTNAME36	_T("data/texture/HS/moji/z.png")
#define TEXT_NO		(36)
#define TEXTNAME2_1	_T("data/texture/HS/text1.png")
#define TEXTNAME2_2	_T("data/texture/HS/text2.png")
#define TEXTNAME2_3	_T("data/texture/HS/text3.png")
#define TEXTNAME2_4	_T("data/texture/HS/text4.png")
#define TEXTNAME2_5	_T("data/texture/HS/text5.png")
#define TEXTNAME2_6	_T("data/texture/HS/text6.png")
#define TEXTNAME2_7	_T("data/texture/HS/text7.png")
#define TEXT_NO2		(7)

//******グローバル変数******
static GAMETEXT_2D	textno[TEXT_NO];
static GAMETEXT_2D	textno2[TEXT_NO];

// 初期化//=============================================================================
//=============================================================================
HRESULT InitHS_Gametext1()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	//テクスチャ
	hr = CreateTextureFromFile(pDevice, TEXTNAME1, &textno[0].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME2, &textno[1].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME3, &textno[2].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME4, &textno[3].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME5, &textno[4].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME6, &textno[5].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME7, &textno[6].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME8, &textno[7].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME9, &textno[8].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME10, &textno[9].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME11, &textno[10].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME12, &textno[11].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME13, &textno[12].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME14, &textno[13].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME15, &textno[14].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME16, &textno[15].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME17, &textno[16].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME18, &textno[17].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME19, &textno[18].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME20, &textno[19].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME21, &textno[20].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME22, &textno[21].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME23, &textno[22].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME24, &textno[23].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME25, &textno[24].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME26, &textno[25].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME27, &textno[26].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME28, &textno[27].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME29, &textno[28].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME30, &textno[29].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME31, &textno[30].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME32, &textno[31].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME33, &textno[32].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME34, &textno[33].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME35, &textno[34].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME36, &textno[35].g_pHS_Gametext1ure);
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
	hr = CreateTextureFromFile(pDevice, TEXTNAME2_1, &textno2[0].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME2_2, &textno2[1].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME2_3, &textno2[2].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME2_4, &textno2[3].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME2_5, &textno2[4].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME2_6, &textno2[5].g_pHS_Gametext1ure);
	hr = CreateTextureFromFile(pDevice, TEXTNAME2_7, &textno2[6].g_pHS_Gametext1ure);
	for (int i = 0; i < TEXT_NO2; i++)
	{
		textno2[i].g_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		textno2[i].g_Size = XMFLOAT2(253, 70);
		textno2[i].g_Angle = 0.0f;
		textno2[i].g_vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		textno2[i].g_Scale = XMFLOAT2(1.0f, 1.0f);
		textno2[i].g_TexCoord = XMFLOAT2(1.0f, 1.0f);
		textno2[i].g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
		textno2[i].Alfa = 1.0f;
		textno2[i].AlfaAd = 0.0f;
	}
	textno2[0].g_Position = XMFLOAT3(-400.0f, 300.0f, 0.0f);
	textno2[1].g_Position = XMFLOAT3(-450.0f, -300.0f, 0.0f);
	textno2[2].g_Position = XMFLOAT3(450.0f, -300.0f, 0.0f);
	textno2[3].g_Position = XMFLOAT3(250.0f, 0.0f, 0.0f);
	textno2[4].g_Position = XMFLOAT3(250.0f, 100.0f, 0.0f);
	textno2[5].g_Position = XMFLOAT3(-150.0f, -300.0f, 0.0f);
	textno2[6].g_Position = XMFLOAT3(0.0f, 300.0f, 0.0f);
	textno2[0].g_Size = XMFLOAT2(359, 58);
	textno2[3].g_Size = XMFLOAT2(386, 131);
	textno2[4].g_Size = XMFLOAT2(359, 58);
	textno2[6].g_Size = XMFLOAT2(359, 58);
	return hr;
}


//=============================================================================
// 終了
//=============================================================================
void UninitHS_Gametext1()
{
	for (int i = 0; i < TEXT_NO; i++)
	{
		SAFE_RELEASE(textno[i].g_pHS_Gametext1ure);
	}
	for (int i = 0; i < TEXT_NO2; i++)
	{
		SAFE_RELEASE(textno2[i].g_pHS_Gametext1ure);
	}
}

//=============================================================================
// 更新
//=============================================================================
void UpdateHS_Gametext1()
{
	for (int i = 0; i < TEXT_NO; i++)
	{
		textno[i].g_Position.x += textno[i].g_vel.x;
		textno[i].g_Position.y += textno[i].g_vel.y;
		textno[i].Alfa += textno[i].AlfaAd;
		if (textno[i].Alfa >= 1.0f)textno[i].Alfa = 1.0f;
		if (textno[i].Alfa <= 0.0f)textno[i].Alfa = 0.0f;
		if (textno[i].Alfa >= 1.0f || textno[i].Alfa <= 0.0f)textno[i].AlfaAd = -textno[i].AlfaAd;
	}
	for (int i = 0; i < TEXT_NO2; i++)
	{
		textno2[i].g_Position.x += textno2[i].g_vel.x;
		textno2[i].g_Position.y += textno2[i].g_vel.y;
		textno2[i].Alfa += textno2[i].AlfaAd;
		if (textno2[i].Alfa >= 1.0f)textno2[i].Alfa = 1.0f;
		if (textno2[i].Alfa <= 0.0f)textno2[i].Alfa = 0.0f;
		if (textno2[i].Alfa >= 1.0f || textno2[i].Alfa <= 0.0f)textno2[i].AlfaAd = -textno2[i].AlfaAd;
	}
}

//=============================================================================
// 描画
//=============================================================================
void Draw_HS_Gametext1(int i)
{
	SetPolygonAlpha(textno[i].Alfa);
	//ポリゴンの情報設定
	SetPolygonPos(textno[i].g_Position.x, textno[i].g_Position.y);
	SetPolygonSize(textno[i].g_Size.x, textno[i].g_Size.y);
	SetPolygonAngle(textno[i].g_Angle);
	//degree(デグリー)値
	SetPolygonUV(textno[i].g_TexCoord.x, textno[i].g_TexCoord.y);		  //左上のUV座標
	SetPolygonFrameSize(textno[i].g_TexFrameSize.x, textno[i].g_TexFrameSize.y);  //横幅縦幅
	SetPolygonTexture(textno[i].g_pHS_Gametext1ure);	  //テクスチャ指定

	// ポリゴンの描画処理
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	SetPolygonAlpha(1.0f);
	SetPolygonColor(1.0f, 1.0f, 1.0f);
}

void Draw_HS_Gametext1All(int i, XMFLOAT2 pos,XMFLOAT2 size)
{
	SetPolygonAlpha(textno[i].Alfa);
	//ポリゴンの情報設定
	SetPolygonPos(pos.x, pos.y);
	SetPolygonSize(size.x, size.y);
	SetPolygonAngle(textno[i].g_Angle);
	//degree(デグリー)値
	SetPolygonUV(textno[i].g_TexCoord.x, textno[i].g_TexCoord.y);		  //左上のUV座標
	SetPolygonFrameSize(textno[i].g_TexFrameSize.x, textno[i].g_TexFrameSize.y);  //横幅縦幅
	SetPolygonTexture(textno[i].g_pHS_Gametext1ure);	  //テクスチャ指定

	// ポリゴンの描画処理
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	SetPolygonAlpha(1.0f);
}

void Draw_HS_Gametext2(int i)
{
	SetPolygonAlpha(textno2[i].Alfa);
	//ポリゴンの情報設定
	SetPolygonPos(textno2[i].g_Position.x, textno2[i].g_Position.y);
	SetPolygonSize(textno2[i].g_Size.x, textno2[i].g_Size.y);
	SetPolygonAngle(textno2[i].g_Angle);
	//degree(デグリー)値
	SetPolygonUV(textno2[i].g_TexCoord.x, textno2[i].g_TexCoord.y);		  //左上のUV座標
	SetPolygonFrameSize(textno2[i].g_TexFrameSize.x, textno2[i].g_TexFrameSize.y);  //横幅縦幅
	SetPolygonTexture(textno2[i].g_pHS_Gametext1ure);	  //テクスチャ指定

	// ポリゴンの描画処理
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	SetPolygonAlpha(1.0f);
	SetPolygonColor(1.0f, 1.0f, 1.0f);
}

GAMETEXT_2D GetGAMETEXT_2Ddata(int no)
{
	return textno2[no];
}