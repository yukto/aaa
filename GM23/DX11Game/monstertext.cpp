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

//******定数宣言******
#define TEXTNAME1	_T("data/texture/monster/card.png")
#define TEXTNAME2	_T("data/texture/monster/dodai2.png")
#define TEXTNAME3	_T("data/texture/monster/かめ.png")
#define TEXTNAME4	_T("data/texture/monster/クリオネ.png")
#define TEXTNAME5	_T("data/texture/monster/こけ.png")
#define TEXTNAME6	_T("data/texture/monster/こけー.png")
#define TEXTNAME7	_T("data/texture/monster/ゴジラ.png")
#define TEXTNAME8	_T("data/texture/monster/スチーム.png")
#define TEXTNAME9	_T("data/texture/monster/スライム.png")
#define TEXTNAME10	_T("data/texture/monster/どら.png")
#define TEXTNAME11	_T("data/texture/monster/にく.png")
#define TEXTNAME12	_T("data/texture/monster/にょろ.png")
#define TEXTNAME13	_T("data/texture/monster/ばーん.png")
#define TEXTNAME14	_T("data/texture/monster/ばーん1.png")
#define TEXTNAME15	_T("data/texture/monster/ブラックタイガー.png")
#define TEXTNAME16	_T("data/texture/monster/ミミック2.png")
#define TEXTNAME17	_T("data/texture/monster/メガネ.png")
#define TEXTNAME18	_T("data/texture/monster/らいがー.png")
#define TEXTNAME19	_T("data/texture/monster/人玉.png")
#define TEXTNAME20	_T("data/texture/monster/石.png")
#define TEXTNAME21	_T("data/texture/monster/妖精.png")
#define TEXTNAME22	_T("data/texture/monster/妖精サンプル.png")
#define TEXT_NO		(22)

typedef struct {
	ID3D11ShaderResourceView*	g_pTexture;
	XMFLOAT3		g_Position;		//座標
	XMFLOAT2		g_Size;			//サイズ
	float			g_Angle;		//回転角度
	XMFLOAT3		g_vel;
	XMFLOAT2		g_Scale;
	XMFLOAT2		g_TexCoord;		//テクスチャ座標(ポリゴンの左上)
	XMFLOAT2		g_TexFrameSize; //テクスチャを張り付けるサイズ
	float			Alfa;
	float			AlfaAd;
} TEXT_1;

//******グローバル変数******
static TEXT_1	textno[TEXT_NO];

// 初期化//=============================================================================
//=============================================================================
HRESULT InitMonsterText()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	//テクスチャ
	hr = CreateTextureFromFile(pDevice, TEXTNAME1, &textno[0].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME2, &textno[1].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME3, &textno[2].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME4, &textno[3].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME5, &textno[4].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME6, &textno[5].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME7, &textno[6].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME8, &textno[7].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME9, &textno[8].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME10, &textno[9].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME11, &textno[10].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME12, &textno[11].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME13, &textno[12].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME14, &textno[13].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME15, &textno[14].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME16, &textno[15].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME17, &textno[16].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME18, &textno[17].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME19, &textno[18].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME20, &textno[19].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME21, &textno[20].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME22, &textno[21].g_pTexture);
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
	return hr;
}


//=============================================================================
// 終了
//=============================================================================
void UninitMonsterText()
{
	for (int i = 0; i < TEXT_NO; i++)
	{
		SAFE_RELEASE(textno[i].g_pTexture);
	}
}

//=============================================================================
// 更新
//=============================================================================
void UpdateMonsterText()
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
}

//=============================================================================
// 描画
//=============================================================================
void DrawMonsterText(int no)
{
	for (int i = 0; i < TEXT_NO; i++)
	{
		if (i > 2 && i != no)continue;
		SetPolygonAlpha(textno[i].Alfa);
		//ポリゴンの情報設定
		SetPolygonPos(textno[i].g_Position.x, textno[i].g_Position.y);
		SetPolygonSize(textno[i].g_Size.x, textno[i].g_Size.y);
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
}

void DrawMonsterTextAll(int i, XMFLOAT2 pos,XMFLOAT2 size)
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