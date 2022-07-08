//=============================================================================
//
// 弾処理 [bullet.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"

// マクロ定義
#define MAX_BILLBOARD		(6)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
int FireBillboard(XMFLOAT3 pos, XMFLOAT3 dir, int no);