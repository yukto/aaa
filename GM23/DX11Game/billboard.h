//=============================================================================
//
// �e���� [bullet.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"

// �}�N����`
#define MAX_BILLBOARD		(6)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
int FireBillboard(XMFLOAT3 pos, XMFLOAT3 dir, int no);