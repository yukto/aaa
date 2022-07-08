//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
//
//=============================================================================
#include "fade.h"
#include"Texture.h"
#include "polygon.h"

// �}�N����`
#define FADE_POS_X		(0)		// �\���ʒuX
#define FADE_POS_Y		(0)		// �\���ʒuY
#define FADE_SIZE_X		(SCREEN_WIDTH)	// �T�C�YX
#define FADE_SIZE_Y		(SCREEN_HEIGHT)	// �T�C�YY

#define FADE_RED		(0.0f)
#define FADE_GREEN		(0.0f)
#define FADE_BLUE		(0.0f)

#define TEXTNAME1	_T("data/texture/HS/�f��.png")
#define TEXTNAME2	_T("data/texture/HS/�f��2.png")
#define TEXTNAME3	_T("data/texture/HS/�f��3.png")
#define TEXTNAME4	_T("data/texture/HS/�f��4.png")
#define TEXTNAME5	_T("data/texture/HS/�f��5.png")
#define TEXTNAME6	_T("data/texture/HS/�f��6.png")
#define TEXTNAME6	_T("data/texture/HS/�f��6.png")
#define TEXTNAME7	_T("data/texture/clear01.png")
#define TEXT_NO		(300)
// �\���̒�`
typedef struct {
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
	bool			nState;
} FADE_2D;
// �v���g�^�C�v�錾
// �O���[�o���ϐ�
static float			g_fAlpha = 1.0f;	// �����x
static E_FADE			g_nFade = E_FADE_IN;	// �t�F�[�h�̏��
static E_TYPE_SCENE		g_stateNext = SCENE_TITLE;	// �t�F�[�h��̏��
static int				g_nFrame = 30;	// �t�F�[�h�t���[����
static FADE_2D			textno[TEXT_NO];
static ID3D11ShaderResourceView*	g_pTexture[7];

// ����������
HRESULT InitFade( void )
{
	g_fAlpha = 0.0f;			// �ŏ��̓t�F�[�h�C������
	g_nFade = E_FADE_NONE;
	g_stateNext = SCENE_TITLE;
	g_nFrame = 30;

	ID3D11Device* pDevice = GetDevice();

	//�e�N�X�`��
	CreateTextureFromFile(pDevice, TEXTNAME1, &g_pTexture[0]);
	CreateTextureFromFile(pDevice, TEXTNAME2, &g_pTexture[1]);
	CreateTextureFromFile(pDevice, TEXTNAME3, &g_pTexture[2]);
	CreateTextureFromFile(pDevice, TEXTNAME4, &g_pTexture[3]);
	CreateTextureFromFile(pDevice, TEXTNAME5, &g_pTexture[4]);
	CreateTextureFromFile(pDevice, TEXTNAME6, &g_pTexture[5]);
	CreateTextureFromFile(pDevice, TEXTNAME7, &g_pTexture[6]);
	for (int i = 0; i < TEXT_NO; i++)
	{
		textno[i].g_Position = XMFLOAT3(SCREEN_CENTER_X + 200.0f + (float)(rand() % 1400),0.0f + (float)(rand() % 760 - 380), 0.0f);
		textno[i].g_Size = XMFLOAT2(200, 200);
		textno[i].g_Angle = 0.0f;
		textno[i].g_vel = XMFLOAT3(-10.0f - (float)(rand() % 6), 0.0f, 0.0f);
		textno[i].g_Scale = XMFLOAT2(1.0f, 1.0f);
		textno[i].g_TexCoord = XMFLOAT2(1.0f, 1.0f);
		textno[i].g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
		textno[i].Alfa = 1.0f;
		textno[i].AlfaAd = 0.0f;
		textno[i].AngleAd = (float)(rand() % 4 + 1);
		textno[i].nState = false;
	}
	textno[TEXT_NO - 1].g_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	textno[TEXT_NO - 1].g_Size = XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
	textno[TEXT_NO - 1].g_vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	textno[TEXT_NO - 1].AngleAd = 0.0f;
	return S_OK;
}

void UninitFade( void )
{
}

void UpdateFade( void )
{
	for (int i = 0; i < TEXT_NO -1; i++)
	{
		if (!textno[i].nState)continue;
		textno[i].g_Angle += textno[i].AngleAd;
		textno[i].g_Position.x += textno[i].g_vel.x;
	}
	for (int i = 0; i < TEXT_NO - 1; i++)
	{
		if (textno[i].g_Position.x > SCREEN_CENTER_X + 400)break;
		if(i == TEXT_NO - 2 && g_nFade == E_FADE_OUT && g_fAlpha < 1.0f)g_fAlpha += 0.03f;
		else if (i == TEXT_NO - 2 && g_nFade == E_FADE_IN)g_fAlpha -= 0.03f;
	}
	for (int i = 0; i < TEXT_NO - 1; i++)
	{
		if (textno[i].g_Position.x > -SCREEN_CENTER_X - 150)break;
		if (i == TEXT_NO - 2 && g_nFade == E_FADE_OUT)g_fAlpha = 1.1f;
		else if (i == TEXT_NO - 2 && g_nFade == E_FADE_IN)g_fAlpha = -0.1f;
	}
	// �P�t���[�����Ƃ̍X�V����
	switch( g_nFade )
	{
	case E_FADE_OUT:	// �t�F�[�h�A�E�g
		if (g_fAlpha == 1.1f)
		{	// �t�F�[�h�A�E�g���I������̂Ńt�F�[�h�C���ɕύX
			g_fAlpha = 1.0f;
			g_nFade  = E_FADE_LOAD;
			for (int i = 0; i < TEXT_NO - 1; i++)
			{
				textno[i].g_Position = XMFLOAT3(SCREEN_CENTER_X + 200.0f + (float)(rand() % 1400), 0.0f + (float)(rand() % 760 - 380), 0.0f);
				textno[i].nState = false;
			}
		}
		break;
	case E_FADE_LOAD:
		StartSceneChange(g_stateNext);
		g_nFade = E_FADE_IN;
		for (int i = 0; i < TEXT_NO - 1; i++)
		{
			textno[i].nState = true;
		}
		break;
	case E_FADE_IN:	// �t�F�[�h�C��
		if (g_fAlpha == -0.1f)
		{
				// �t�F�[�h�C�����I�����
			g_fAlpha = 0.0f;
			g_nFade = E_FADE_NONE;
			for (int i = 0; i < TEXT_NO - 1; i++)
			{
				textno[i].g_Position = XMFLOAT3(SCREEN_CENTER_X + 200.0f + (float)(rand() % 1400), 0.0f + (float)(rand() % 760 - 380), 0.0f);
				textno[i].nState = false;
			}
		}
		break;
	}

}

void DrawFade( void )
{
	if(g_nFade == E_FADE_NONE)return;
	SetPolygonAlpha(g_fAlpha);
	//�|���S���̏��ݒ�
	SetPolygonPos(textno[TEXT_NO - 1].g_Position.x, textno[TEXT_NO - 1].g_Position.y);
	SetPolygonSize(textno[TEXT_NO - 1].g_Size.x, textno[TEXT_NO - 1].g_Size.y);
	SetPolygonAngle(textno[TEXT_NO - 1].g_Angle);
	//degree(�f�O���[)�l
	SetPolygonUV(textno[TEXT_NO - 1].g_TexCoord.x, textno[TEXT_NO - 1].g_TexCoord.y);		  //�����UV���W
	SetPolygonFrameSize(textno[TEXT_NO - 1].g_TexFrameSize.x, textno[TEXT_NO - 1].g_TexFrameSize.y);  //�����c��
	SetPolygonTexture(g_pTexture[6]);	  //�e�N�X�`���w��

	// �|���S���̕`�揈��
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	for (int i = 0; i < TEXT_NO - 1; i++)
	{
		SetPolygonAlpha(textno[i].Alfa);
		//�|���S���̏��ݒ�
		SetPolygonPos(textno[i].g_Position.x, textno[i].g_Position.y);
		SetPolygonSize(textno[i].g_Size.x, textno[i].g_Size.y);
		SetPolygonAngle(textno[i].g_Angle);
		//degree(�f�O���[)�l
		SetPolygonUV(textno[i].g_TexCoord.x, textno[i].g_TexCoord.y);		  //�����UV���W
		SetPolygonFrameSize(textno[i].g_TexFrameSize.x, textno[i].g_TexFrameSize.y);  //�����c��
		SetPolygonTexture(g_pTexture[i % 6]);	  //�e�N�X�`���w��

		// �|���S���̕`�揈��
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
		DrawPolygon(pDeviceContext);
	}
	SetPolygonAlpha(1.0f);
	SetPolygonAngle(0.0f);
	SetPolygonColor(1.0f, 1.0f, 1.0f);
}

// �t�F�[�h�J�n
// stateNext:
// nFrame:
void StartFade( E_TYPE_SCENE stateNext, int nFrame/* = 30 */)
{
	if (GetFade() != E_FADE_NONE) return;
	g_nFade = E_FADE_OUT;
	g_stateNext = stateNext;
	if (nFrame <= 0) nFrame = 1;
	g_nFrame = nFrame;
	for (int i = 0; i < TEXT_NO - 1; i++)
	{
		textno[i].nState = true;
	}
}

// ���݃t�F�[�h���ł����H
E_FADE GetFade()
{
	return g_nFade;
}

float GetFadeAlpha()
{
	return g_fAlpha;
}