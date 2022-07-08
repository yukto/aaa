//=============================================================================
//
// プレイヤー [Text.h]
// Author : SHOUEI HIRAMATSU 
//
//------------------------------------
//開発履歴:2021/06/23 作成開始:
//				06/** ******機能の実装
//=============================================================================

#pragma once

//******インクルード******
#include"main.h"

typedef struct {
	ID3D11ShaderResourceView*	g_pHS_Gametext1ure;
	XMFLOAT3		g_Position;		//座標
	XMFLOAT2		g_Size;			//サイズ
	float			g_Angle;		//回転角度
	XMFLOAT3		g_vel;
	XMFLOAT2		g_Scale;
	XMFLOAT2		g_TexCoord;		//テクスチャ座標(ポリゴンの左上)
	XMFLOAT2		g_TexFrameSize; //テクスチャを張り付けるサイズ
	float			Alfa;
	float			AlfaAd;
} GAMETEXT_2D;

//******プロトタイプ宣言******
HRESULT InitHS_Gametext1();  //初期化
void UninitHS_Gametext1();
void UpdateHS_Gametext1();
void Draw_HS_Gametext1(int i);     //描画
void Draw_HS_Gametext1All(int i, XMFLOAT2 pos, XMFLOAT2 size);
void Draw_HS_Gametext2(int i);
GAMETEXT_2D GetGAMETEXT_2Ddata(int no);