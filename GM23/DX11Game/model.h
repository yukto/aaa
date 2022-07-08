//=============================================================================
//
// ���f������ [model.h]
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
	int					nState;		//��ԁi0:���g�p1:�ʏ�j
	int					Anime;
}tModel;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void RotationSwitchOn();
bool GetRotationSwitch();
void AnimeSwitch(int no, int no2);