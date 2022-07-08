//=============================================================================
//
// �Q�[�W���� [gauge.h]
//
//=============================================================================
#pragma once

#include "main.h"

// �}�N����`
#define GAUGE_MAX	(100)

// �v���g�^�C�v�錾
HRESULT InitGauge(void);
HRESULT InitStartGauge(void);
void UninitGauge(void);
void UninitStartGauge(void);
void UpdateGauge(void);
// ���W�͍��[���w��
void DrawGauge(XMFLOAT2 pos, float percent);
void DrawGauge2( XMFLOAT2 pos, float percent );
void DrawGauge3(XMFLOAT2 pos, XMFLOAT2 size, float percent, int no);
void DrawGaugeLeft3(XMFLOAT2 pos, XMFLOAT2 size, float percent, int no);
void DrawLoadGauge(float percent);