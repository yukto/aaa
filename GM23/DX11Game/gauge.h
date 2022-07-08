//=============================================================================
//
// ゲージ処理 [gauge.h]
//
//=============================================================================
#pragma once

#include "main.h"

// マクロ定義
#define GAUGE_MAX	(100)

// プロトタイプ宣言
HRESULT InitGauge(void);
HRESULT InitStartGauge(void);
void UninitGauge(void);
void UninitStartGauge(void);
void UpdateGauge(void);
// 座標は左端を指定
void DrawGauge(XMFLOAT2 pos, float percent);
void DrawGauge2( XMFLOAT2 pos, float percent );
void DrawGauge3(XMFLOAT2 pos, XMFLOAT2 size, float percent, int no);
void DrawGaugeLeft3(XMFLOAT2 pos, XMFLOAT2 size, float percent, int no);
void DrawLoadGauge(float percent);