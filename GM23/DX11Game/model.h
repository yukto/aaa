//=============================================================================
//
// モデル処理 [model.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"
#include "AssimpModel.h"

typedef struct _tModel
{
	CAssimpModel		model;
	XMFLOAT4X4			mtxWorld;
	XMFLOAT3			posModel;
	XMFLOAT3			rotModel;
	XMFLOAT3			sclModel;
	XMFLOAT3			velModel;
	int					nState;		//状態（0:未使用1:通常）
	int					Anime;
}tModel;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void RotationSwitchOn();
bool GetRotationSwitch();
void AnimeSwitch(int no, int no2);