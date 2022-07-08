//=============================================================================
//
// �v���C���[ [Text.cpp]
// Author : SHOUEI HIRAMATSU 
//
//------------------------------------
//�J������:2021/06/23 �쐬�J�n:
//				06/** ******�@�\�̎���
//=============================================================================

//���j���[���
#ifdef _DEBUG
#include "debugproc.h"
#endif // _DEBUG

//******�C���N���[�h******
#include"MiniGametext.h"
#include"Texture.h"
#include "polygon.h"
#include "input.h"
#include "collision.h"
#include "sceneGame.h"
#include "HS_effect.h"

//******�萔�錾******
#define TEXTNAME1	_T("data/texture/messagewindow.png")
#define TEXTNAME2	_T("data/texture/HS/�o�g��.png")
#define TEXTNAME3	_T("data/texture/HS/�g���[�j���O.png")
#define TEXTNAME4	_T("data/texture/HS/�ۑ�.png")
#define TEXTNAME2_1	_T("data/texture/messagewindow.png")
#define TEXTNAME2_2	_T("data/texture/HS/�o�g��.png")
#define TEXTNAME2_3	_T("data/texture/HS/�g���[�j���O.png")
#define TEXTNAME2_4	_T("data/texture/HS/�ۑ�.png")
#define TEXT_NO		(15)
#define WOODNO		(3)

#define EXPLOSION_TEXTURENAME2		"data/texture/HS/shock.png"		// �|���S���ɕ\��������摜
#define EXPLOSION_TEXTURENAME3		"data/texture/HS/block1.png"		// �|���S���ɕ\��������摜

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
	float			AngleAd;
	int				MNo;
	bool			State;
} TEXTGAME_2D;

typedef struct {
	int			HP;
	int			SCORE;
} PLAYER;

//******�O���[�o���ϐ�******
static TEXTGAME_2D	Gtextno[TEXT_NO];
static PLAYER	player;
static int		MiniGameNo = 0;
static GameEffect		effect[2];


//=============================================================================
// ������
//=============================================================================
HRESULT InitMiniGameText(int no)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	MiniGameNo = no;
	//�e�N�X�`��
	switch (MiniGameNo)
	{
	case 0:
		hr = CreateTextureFromFile(pDevice, TEXTNAME1, &Gtextno[0].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME2, &Gtextno[1].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME3, &Gtextno[2].g_pTexture);
		for (int a = 3; a < TEXT_NO; a++)
		{
			hr = CreateTextureFromFile(pDevice, TEXTNAME4, &Gtextno[a].g_pTexture);
		}
		for (int i = 0; i < TEXT_NO; i++)
		{
			Gtextno[i].g_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
			Gtextno[i].g_Size = XMFLOAT2(100, 100);
			Gtextno[i].g_Angle = 0.0f;
			Gtextno[i].g_vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
			Gtextno[i].g_Scale = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].g_TexCoord = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].Alfa = 1.0f;
			Gtextno[i].AlfaAd = 0.0f;
			Gtextno[i].AngleAd = 0.0f;
			Gtextno[i].State = true;
			if (i >= WOODNO)
			{
				Gtextno[i].AngleAd = 0.5f;
				Gtextno[i].MNo = rand() % 26 + 65;
				Gtextno[i].g_Position = XMFLOAT3(300.0f + 150 * i, 0.0f, 0.0f);
				Gtextno[i].g_vel = XMFLOAT3(-3.0f, 0.0f, 0.0f);
			}
		}
		Gtextno[0].g_Size = XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
		Gtextno[1].g_Size = XMFLOAT2(100, 200);
		Gtextno[2].g_Position = XMFLOAT3(100.0f, 0.0f, 0.0f);
		effect[0].HS_InitExplosion((char*)EXPLOSION_TEXTURENAME2, XMFLOAT2(100, 100), XMFLOAT2(5, 4), 5);
		effect[1].HS_InitExplosion((char*)EXPLOSION_TEXTURENAME3, XMFLOAT2(100, 100), XMFLOAT2(5, 6), 2);
		break;
	case 1:

		break;
	default:
		hr = CreateTextureFromFile(pDevice, TEXTNAME1, &Gtextno[0].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME2, &Gtextno[1].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME3, &Gtextno[2].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME1, &Gtextno[3].g_pTexture);
		hr = CreateTextureFromFile(pDevice, TEXTNAME1, &Gtextno[4].g_pTexture);
		for (int i = 0; i < TEXT_NO; i++)
		{
			Gtextno[i].g_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
			Gtextno[i].g_Size = XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
			Gtextno[i].g_Angle = 0.0f;
			Gtextno[i].g_vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
			Gtextno[i].g_Scale = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].g_TexCoord = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
			Gtextno[i].Alfa = 1.0f;
			Gtextno[i].AlfaAd = 0.0f;
			Gtextno[i].State = true;
		}
		break;
	}
	player.HP = 100;
	player.SCORE = 0;
	return hr;
}


//=============================================================================
// �I��
//=============================================================================
void UninitMiniGameText()
{
	switch (MiniGameNo)
	{
	case 0:
		for (int i = 0; i < TEXT_NO; i++)
		{
			SAFE_RELEASE(Gtextno[i].g_pTexture);
		}
		effect[0].HS_UninitExplosion();
		effect[1].HS_UninitExplosion();
		break;
	default:
		break;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void UpdateMiniGameText()
{
	static int Kno;
	Kno = GetTrigerKeyNo();
	switch (MiniGameNo)
	{
	case 0:
		effect[0].HS_UpdateExplosion();
		effect[1].HS_UpdateExplosion();
		for (int i = WOODNO; i < TEXT_NO; i++)
		{
			if (CollisionBB(&(XMFLOAT2(Gtextno[i].g_Position.x, Gtextno[i].g_Position.y)),
				&Gtextno[i].g_Size, &(XMFLOAT2(Gtextno[2].g_Position.x, Gtextno[2].g_Position.y)), &Gtextno[2].g_Size)
				&& Kno == Gtextno[i].MNo && Gtextno[i].State)
			{
				Gtextno[i].g_vel = XMFLOAT3(0.0f, -1.0f, 0.0f);
				player.SCORE += 100 - (int)abs(Gtextno[2].g_Position.x - Gtextno[i].g_Position.x);
				Gtextno[i].State = false;
				effect[1].HS_SetExplosion(Gtextno[2].g_Position);
				break;
			}
			if (Gtextno[1].g_Position.x + Gtextno[1].g_Size.x > Gtextno[i].g_Position.x && Gtextno[i].State)
			{
				effect[0].HS_SetExplosion(Gtextno[1].g_Position);
				Gtextno[i].State = false;
			}

		}
		for (int i = 0; i < TEXT_NO; i++)
		{
			if (i >= WOODNO)Gtextno[i].g_vel.y *= 1.3f;
			Gtextno[i].g_Position.x += Gtextno[i].g_vel.x;
			Gtextno[i].g_Position.y += Gtextno[i].g_vel.y;
			Gtextno[i].Alfa += Gtextno[i].AlfaAd;
			if (Gtextno[i].Alfa >= 1.0f)Gtextno[i].Alfa = 1.0f;
			if (Gtextno[i].Alfa <= 0.0f)Gtextno[i].Alfa = 0.0f;
			if (Gtextno[i].Alfa >= 1.0f || Gtextno[i].Alfa <= 0.0f)Gtextno[i].AlfaAd = -Gtextno[i].AlfaAd;
			Gtextno[i].g_Angle += Gtextno[i].AngleAd;
		}
		break;
	case 1:
		break;
	default:
		Gtextno[1].g_vel.x = 0.0f;
		Gtextno[1].g_vel.y -= 1.0f;
		if (GetKeyTrigger(VK_SPACE))Gtextno[1].g_vel.y = 15.0f;
		if (GetKeyPress(VK_A))Gtextno[1].g_vel.x = -5.0f;
		if (GetKeyPress(VK_D))Gtextno[1].g_vel.x = 5.0f;
		if (Gtextno[1].g_Position.y < -200.0f)
		{
			Gtextno[1].g_Position.y = -200.0f;
			Gtextno[1].g_vel.y = 0.0f;
		}
		break;
	}
}

void Draw_MiniGameTextAll(int i, XMFLOAT2 sc)
{
	if (abs(Gtextno[i].g_Position.x) > SCREEN_CENTER_X ||
		abs(Gtextno[i].g_Position.y) > SCREEN_CENTER_Y)return;
	SetPolygonAlpha(Gtextno[i].Alfa);
	//�|���S���̏��ݒ�
	SetPolygonPos(Gtextno[i].g_Position.x * sc.x, Gtextno[i].g_Position.y * sc.y);
	SetPolygonSize(Gtextno[i].g_Size.x * sc.x, Gtextno[i].g_Size.y * sc.y);
	SetPolygonAngle(Gtextno[i].g_Angle);
	//degree(�f�O���[)�l
	SetPolygonUV(Gtextno[i].g_TexCoord.x, Gtextno[i].g_TexCoord.y);		  //�����UV���W
	SetPolygonFrameSize(Gtextno[i].g_TexFrameSize.x, Gtextno[i].g_TexFrameSize.y);  //�����c��
	SetPolygonTexture(Gtextno[i].g_pTexture);	  //�e�N�X�`���w��

	// �|���S���̕`�揈��
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	SetPolygonAlpha(1.0f);
}

XMFLOAT2 GetMiniGameTextPos(int no)
{
	return XMFLOAT2(Gtextno[no].g_Position.x, Gtextno[no].g_Position.y);
}

int GetMiniGameTextMNo(int no)
{
	return Gtextno[no].MNo;
}

void DrwaEffectText()
{
	switch (0)
	{
	case 0:
		effect[0].HS_DrawExplosion();
		effect[1].HS_DrawExplosion();
		break;
	default:
		break;
	}
}

int GetMiniGamePLAYER()
{
	return player.SCORE;
}