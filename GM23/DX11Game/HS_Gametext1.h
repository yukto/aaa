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
	ID3D11ShaderResourceView*	g_pHS_Gametext1ure;
	XMFLOAT3		g_Position;		//���W
	XMFLOAT2		g_Size;			//�T�C�Y
	float			g_Angle;		//��]�p�x
	XMFLOAT3		g_vel;
	XMFLOAT2		g_Scale;
	XMFLOAT2		g_TexCoord;		//�e�N�X�`�����W(�|���S���̍���)
	XMFLOAT2		g_TexFrameSize; //�e�N�X�`���𒣂�t����T�C�Y
	float			Alfa;
	float			AlfaAd;
} GAMETEXT_2D;

//******�v���g�^�C�v�錾******
HRESULT InitHS_Gametext1();  //������
void UninitHS_Gametext1();
void UpdateHS_Gametext1();
void Draw_HS_Gametext1(int i);     //�`��
void Draw_HS_Gametext1All(int i, XMFLOAT2 pos, XMFLOAT2 size);
void Draw_HS_Gametext2(int i);
GAMETEXT_2D GetGAMETEXT_2Ddata(int no);