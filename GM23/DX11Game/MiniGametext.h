//=============================================================================
//
// �v���C���[ [Text.h]
// Author : SHOUEI HIRAMATSU 
//
//------------------------------------
//�J������:2021/06/23 �쐬�J�n:
//				06/** ******�@�\�̎���
//=============================================================================

#pragma once

//******�C���N���[�h******
#include"main.h"
#include "C_Text.h"

class Titletxet :public CText {
public:
	float Scroll;
	float Scroll1;
	void Update();
};
//******�v���g�^�C�v�錾******
HRESULT InitMiniGameText(int no);  //������
void UninitMiniGameText();
void UpdateMiniGameText();
void Draw_MiniGameTextAll(int i, XMFLOAT2 sc);
XMFLOAT2 GetMiniGameTextPos(int no);
int GetMiniGameTextMNo(int no);
void DrwaEffectText();
int GetMiniGamePLAYER();

