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

typedef struct {
	ID3D11ShaderResourceView*	g_pTexture;
	XMFLOAT3		g_Position;		//���W
	XMFLOAT2		g_Size;			//�T�C�Y
	float			g_Angle;		//��]�p�x
	XMFLOAT3		g_vel;
	XMFLOAT2		g_Scale;
	XMFLOAT2		g_TexCoord;		//�e�N�X�`�����W(�|���S���̍���)
	XMFLOAT2		g_TexFrameSize; //�e�N�X�`���𒣂�t����T�C�Y
	float			Alfa;
	float			AlfaAd;
	int				State;
} TEXT_2D;

//******�v���g�^�C�v�錾******
HRESULT InitText();  //������
void UninitText();
void UpdateText();
void Draw_Text(int i);     //�`��
void Draw_TextAll(int i, XMFLOAT2 pos, XMFLOAT2 size);
void Draw_CompleteNo(int i, XMFLOAT2 pos, float sc);
TEXT_2D GetTextData(int no);
void MenuPosAdo(float pos);
float GetMenuPos();