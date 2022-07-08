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
#include"MiniGametext.h"
#include"Texture.h"
#include "polygon.h"
#include "input.h"
#include "collision.h"
#include "sceneGame.h"
#include "HS_effect.h"

//******定数宣言******
#define TEXTNAME1	_T("data/texture/messagewindow.png")
#define TEXTNAME2	_T("data/texture/HS/バトル.png")
#define TEXTNAME3	_T("data/texture/HS/トレーニング.png")
#define TEXTNAME4	_T("data/texture/HS/丸太.png")
#define TEXTNAME2_1	_T("data/texture/messagewindow.png")
#define TEXTNAME2_2	_T("data/texture/HS/バトル.png")
#define TEXTNAME2_3	_T("data/texture/HS/トレーニング.png")
#define TEXTNAME2_4	_T("data/texture/HS/丸太.png")
#define TEXT_NO		(15)
#define WOODNO		(3)

#define EXPLOSION_TEXTURENAME2		"data/texture/HS/shock.png"		// ポリゴンに表示させる画像
#define EXPLOSION_TEXTURENAME3		"data/texture/HS/block1.png"		// ポリゴンに表示させる画像

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
	float			AngleAd;
	int				MNo;
	bool			State;
} TEXTGAME_2D;

typedef struct {
	int			HP;
	int			SCORE;
} PLAYER;

//******グローバル変数******
static TEXTGAME_2D	Gtextno[TEXT_NO];
static PLAYER	player;
static int		MiniGameNo = 0;
static GameEffect		effect[2];


//=============================================================================
// 初期化
//=============================================================================
HRESULT InitMiniGameText(int no)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	MiniGameNo = no;
	//テクスチャ
	switch (MiniGameNo)
	{
	case 0:
		hr = CreateTextureFromFile(pDevice, TEXTNAME1, &Gtextno[0].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME2, &Gtextno[1].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME3, &Gtextno[2].g_pTexture);
		for (int a = 3; a < TEXT_NO; a++)
		{
			hr = CreateTextureFromFile(pDevice, TEXTNAME4, &Gtextno[a].g_pTexture);
		}
		for (int i = 0; i < TEXT_NO; i++)
		{
			Gtextno[i].g_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
			Gtextno[i].g_Size = XMFLOAT2(100, 100);
			Gtextno[i].g_Angle = 0.0f;
			Gtextno[i].g_vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
			Gtextno[i].g_Scale = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].g_TexCoord = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].Alfa = 1.0f;
			Gtextno[i].AlfaAd = 0.0f;
			Gtextno[i].AngleAd = 0.0f;
			Gtextno[i].State = true;
			if (i >= WOODNO)
			{
				Gtextno[i].AngleAd = 0.5f;
				Gtextno[i].MNo = rand() % 26 + 65;
				Gtextno[i].g_Position = XMFLOAT3(300.0f + 150 * i, 0.0f, 0.0f);
				Gtextno[i].g_vel = XMFLOAT3(-3.0f, 0.0f, 0.0f);
			}
		}
		Gtextno[0].g_Size = XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
		Gtextno[1].g_Size = XMFLOAT2(100, 200);
		Gtextno[2].g_Position = XMFLOAT3(100.0f, 0.0f, 0.0f);
		effect[0].HS_InitExplosion((char*)EXPLOSION_TEXTURENAME2, XMFLOAT2(100, 100), XMFLOAT2(5, 4), 5);
		effect[1].HS_InitExplosion((char*)EXPLOSION_TEXTURENAME3, XMFLOAT2(100, 100), XMFLOAT2(5, 6), 2);
		break;
	case 1:

		break;
	default:
		hr = CreateTextureFromFile(pDevice, TEXTNAME1, &Gtextno[0].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME2, &Gtextno[1].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME3, &Gtextno[2].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME1, &Gtextno[3].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME1, &Gtextno[4].g_pTexture);
		for (int i = 0; i < TEXT_NO; i++)
		{
			Gtextno[i].g_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
			Gtextno[i].g_Size = XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
			Gtextno[i].g_Angle = 0.0f;
			Gtextno[i].g_vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
			Gtextno[i].g_Scale = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].g_TexCoord = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].Alfa = 1.0f;
			Gtextno[i].AlfaAd = 0.0f;
			Gtextno[i].State = true;
		}
		break;
	}
	player.HP = 100;
	player.SCORE = 0;
	return hr;
}


//=============================================================================
// 終了
//=============================================================================
void UninitMiniGameText()
{
	switch (MiniGameNo)
	{
	case 0:
		for (int i = 0; i < TEXT_NO; i++)
		{
			SAFE_RELEASE(Gtextno[i].g_pTexture);
		}
		effect[0].HS_UninitExplosion();
		effect[1].HS_UninitExplosion();
		break;
	default:
		break;
	}
}

//=============================================================================
// 更新
//=============================================================================
void UpdateMiniGameText()
{
	static int Kno;
	Kno = GetTrigerKeyNo();
	switch (MiniGameNo)
	{
	case 0:
		effect[0].HS_UpdateExplosion();
		effect[1].HS_UpdateExplosion();
		for (int i = WOODNO; i < TEXT_NO; i++)
		{
			if (CollisionBB(&(XMFLOAT2(Gtextno[i].g_Position.x, Gtextno[i].g_Position.y)),
				&Gtextno[i].g_Size, &(XMFLOAT2(Gtextno[2].g_Position.x, Gtextno[2].g_Position.y)), &Gtextno[2].g_Size)
				&& Kno == Gtextno[i].MNo && Gtextno[i].State)
			{
				Gtextno[i].g_vel = XMFLOAT3(0.0f, -1.0f, 0.0f);
				player.SCORE += 100 - (int)abs(Gtextno[2].g_Position.x - Gtextno[i].g_Position.x);
				Gtextno[i].State = false;
				effect[1].HS_SetExplosion(Gtextno[2].g_Position);
				break;
			}
			if (Gtextno[1].g_Position.x + Gtextno[1].g_Size.x > Gtextno[i].g_Position.x && Gtextno[i].State)
			{
				effect[0].HS_SetExplosion(Gtextno[1].g_Position);
				Gtextno[i].State = false;
			}

		}
		for (int i = 0; i < TEXT_NO; i++)
		{
			if (i >= WOODNO)Gtextno[i].g_vel.y *= 1.3f;
			Gtextno[i].g_Position.x += Gtextno[i].g_vel.x;
			Gtextno[i].g_Position.y += Gtextno[i].g_vel.y;
			Gtextno[i].Alfa += Gtextno[i].AlfaAd;
			if (Gtextno[i].Alfa >= 1.0f)Gtextno[i].Alfa = 1.0f;
			if (Gtextno[i].Alfa <= 0.0f)Gtextno[i].Alfa = 0.0f;
			if (Gtextno[i].Alfa >= 1.0f || Gtextno[i].Alfa <= 0.0f)Gtextno[i].AlfaAd = -Gtextno[i].AlfaAd;
			Gtextno[i].g_Angle += Gtextno[i].AngleAd;
		}
		break;
	case 1:
		break;
	default:
		Gtextno[1].g_vel.x = 0.0f;
		Gtextno[1].g_vel.y -= 1.0f;
		if (GetKeyTrigger(VK_SPACE))Gtextno[1].g_vel.y = 15.0f;
		if (GetKeyPress(VK_A))Gtextno[1].g_vel.x = -5.0f;
		if (GetKeyPress(VK_D))Gtextno[1].g_vel.x = 5.0f;
		if (Gtextno[1].g_Position.y < -200.0f)
		{
			Gtextno[1].g_Position.y = -200.0f;
			Gtextno[1].g_vel.y = 0.0f;
		}
		break;
	}
}

void Draw_MiniGameTextAll(int i, XMFLOAT2 sc)
{
	if (abs(Gtextno[i].g_Position.x) > SCREEN_CENTER_X ||
		abs(Gtextno[i].g_Position.y) > SCREEN_CENTER_Y)return;
	SetPolygonAlpha(Gtextno[i].Alfa);
	//ポリゴンの情報設定
	SetPolygonPos(Gtextno[i].g_Position.x * sc.x, Gtextno[i].g_Position.y * sc.y);
	SetPolygonSize(Gtextno[i].g_Size.x * sc.x, Gtextno[i].g_Size.y * sc.y);
	SetPolygonAngle(Gtextno[i].g_Angle);
	//degree(デグリー)値
	SetPolygonUV(Gtextno[i].g_TexCoord.x, Gtextno[i].g_TexCoord.y);		  //左上のUV座標
	SetPolygonFrameSize(Gtextno[i].g_TexFrameSize.x, Gtextno[i].g_TexFrameSize.y);  //横幅縦幅
	SetPolygonTexture(Gtextno[i].g_pTexture);	  //テクスチャ指定

	// ポリゴンの描画処理
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	SetPolygonAlpha(1.0f);
}

XMFLOAT2 GetMiniGameTextPos(int no)
{
	return XMFLOAT2(Gtextno[no].g_Position.x, Gtextno[no].g_Position.y);
}

int GetMiniGameTextMNo(int no)
{
	return Gtextno[no].MNo;
}

void DrwaEffectText()
{
	switch (0)
	{
	case 0:
		effect[0].HS_DrawExplosion();
		effect[1].HS_DrawExplosion();
		break;
	default:
		break;
	}
}

int GetMiniGamePLAYER()
{
	return player.SCORE;
}