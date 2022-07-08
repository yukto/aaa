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
#include "C_Text.h"

class Titletxet :public CText {
public:
	float Scroll;
	float Scroll1;
	void Update();
};
//******プロトタイプ宣言******
HRESULT InitMiniGameText(int no);  //初期化
void UninitMiniGameText();
void UpdateMiniGameText();
void Draw_MiniGameTextAll(int i, XMFLOAT2 sc);
XMFLOAT2 GetMiniGameTextPos(int no);
int GetMiniGameTextMNo(int no);
void DrwaEffectText();
int GetMiniGamePLAYER();

