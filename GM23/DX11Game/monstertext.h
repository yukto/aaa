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

//******�v���g�^�C�v�錾******
HRESULT InitMonsterText();  //������
void UninitMonsterText();
void UpdateMonsterText();
void DrawMonsterText(int no);     //�`��
void DrawMonsterTextAll(int i, XMFLOAT2 pos, XMFLOAT2 size);