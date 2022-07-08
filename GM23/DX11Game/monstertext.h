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

//******プロトタイプ宣言******
HRESULT InitMonsterText();  //初期化
void UninitMonsterText();
void UpdateMonsterText();
void DrawMonsterText(int no);     //描画
void DrawMonsterTextAll(int i, XMFLOAT2 pos, XMFLOAT2 size);