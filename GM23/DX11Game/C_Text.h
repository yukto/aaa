#pragma once
#include "main.h"
typedef struct
{
	ID3D11ShaderResourceView*	pTexture;
	XMFLOAT3		Position;		//���W
	XMFLOAT2		Size;			//�T�C�Y
	float			Angle;		//��]�p�x
	XMFLOAT3		vel;
	XMFLOAT2		Scale;
	XMFLOAT2		TexCoord;		//�e�N�X�`�����W(�|���S���̍���)
	XMFLOAT2		TexFrameSize; //�e�N�X�`���𒣂�t����T�C�Y
	float			Alfa;
	float			AlfaAd;
	float			AngleAd;		//��]�p�x
	int				State;
}tText;

class CText
{
public:
	tText		g_text;
	HRESULT InitCText(char* text, XMFLOAT2 size, XMFLOAT3 pos);	//������
	void	UninitCText();	//�I��
	void	UpdateCText();	//�X�V
	void	DrawCText();	//�`��
};
