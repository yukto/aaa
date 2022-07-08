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
#include"text.h"
#include"Texture.h"
#include "polygon.h"
#include"main.h"

//******�萔�錾******
#define TEXTNAME1	_T("data/texture/monster/card.png")
#define TEXTNAME2	_T("data/texture/monster/dodai2.png")
#define TEXTNAME3	_T("data/texture/monster/����.png")
#define TEXTNAME4	_T("data/texture/monster/�N���I�l.png")
#define TEXTNAME5	_T("data/texture/monster/����.png")
#define TEXTNAME6	_T("data/texture/monster/�����[.png")
#define TEXTNAME7	_T("data/texture/monster/�S�W��.png")
#define TEXTNAME8	_T("data/texture/monster/�X�`�[��.png")
#define TEXTNAME9	_T("data/texture/monster/�X���C��.png")
#define TEXTNAME10	_T("data/texture/monster/�ǂ�.png")
#define TEXTNAME11	_T("data/texture/monster/�ɂ�.png")
#define TEXTNAME12	_T("data/texture/monster/�ɂ��.png")
#define TEXTNAME13	_T("data/texture/monster/�΁[��.png")
#define TEXTNAME14	_T("data/texture/monster/�΁[��1.png")
#define TEXTNAME15	_T("data/texture/monster/�u���b�N�^�C�K�[.png")
#define TEXTNAME16	_T("data/texture/monster/�~�~�b�N2.png")
#define TEXTNAME17	_T("data/texture/monster/���K�l.png")
#define TEXTNAME18	_T("data/texture/monster/�炢���[.png")
#define TEXTNAME19	_T("data/texture/monster/�l��.png")
#define TEXTNAME20	_T("data/texture/monster/��.png")
#define TEXTNAME21	_T("data/texture/monster/�d��.png")
#define TEXTNAME22	_T("data/texture/monster/�d���T���v��.png")
#define TEXT_NO		(22)

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
} TEXT_1;

//******�O���[�o���ϐ�******
static TEXT_1	textno[TEXT_NO];

// ������//=============================================================================
//=============================================================================
HRESULT InitMonsterText()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	//�e�N�X�`��
	hr = CreateTextureFromFile(pDevice, TEXTNAME1, &textno[0].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME2, &textno[1].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME3, &textno[2].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME4, &textno[3].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME5, &textno[4].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME6, &textno[5].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME7, &textno[6].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME8, &textno[7].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME9, &textno[8].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME10, &textno[9].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME11, &textno[10].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME12, &textno[11].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME13, &textno[12].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME14, &textno[13].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME15, &textno[14].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME16, &textno[15].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME17, &textno[16].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME18, &textno[17].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME19, &textno[18].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME20, &textno[19].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME21, &textno[20].g_pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTNAME22, &textno[21].g_pTexture);
	for (int i = 0; i < TEXT_NO; i++)
	{
		textno[i].g_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		textno[i].g_Size = XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
		textno[i].g_Angle = 0.0f;
		textno[i].g_vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		textno[i].g_Scale = XMFLOAT2(1.0f, 1.0f);
		textno[i].g_TexCoord = XMFLOAT2(1.0f, 1.0f);
		textno[i].g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
		textno[i].Alfa = 1.0f;
		textno[i].AlfaAd = 0.0f;
	}
	return hr;
}


//=============================================================================
// �I��
//=============================================================================
void UninitMonsterText()
{
	for (int i = 0; i < TEXT_NO; i++)
	{
		SAFE_RELEASE(textno[i].g_pTexture);
	}
}

//=============================================================================
// �X�V
//=============================================================================
void UpdateMonsterText()
{
	for (int i = 0; i < TEXT_NO; i++)
	{
		textno[i].g_Position.x += textno[i].g_vel.x;
		textno[i].g_Position.y += textno[i].g_vel.y;
		textno[i].Alfa += textno[i].AlfaAd;
		if (textno[i].Alfa >= 1.0f)textno[i].Alfa = 1.0f;
		if (textno[i].Alfa <= 0.0f)textno[i].Alfa = 0.0f;
		if (textno[i].Alfa >= 1.0f || textno[i].Alfa <= 0.0f)textno[i].AlfaAd = -textno[i].AlfaAd;
	}
}

//=============================================================================
// �`��
//=============================================================================
void DrawMonsterText(int no)
{
	for (int i = 0; i < TEXT_NO; i++)
	{
		if (i > 2 && i != no)continue;
		SetPolygonAlpha(textno[i].Alfa);
		//�|���S���̏��ݒ�
		SetPolygonPos(textno[i].g_Position.x, textno[i].g_Position.y);
		SetPolygonSize(textno[i].g_Size.x, textno[i].g_Size.y);
		SetPolygonAngle(textno[i].g_Angle);
		//degree(�f�O���[)�l
		SetPolygonUV(textno[i].g_TexCoord.x, textno[i].g_TexCoord.y);		  //�����UV���W
		SetPolygonFrameSize(textno[i].g_TexFrameSize.x, textno[i].g_TexFrameSize.y);  //�����c��
		SetPolygonTexture(textno[i].g_pTexture);	  //�e�N�X�`���w��

		// �|���S���̕`�揈��
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
		DrawPolygon(pDeviceContext);
		SetPolygonAlpha(1.0f);
		SetPolygonColor(1.0f, 1.0f, 1.0f);
	}
}

void DrawMonsterTextAll(int i, XMFLOAT2 pos,XMFLOAT2 size)
{
	SetPolygonAlpha(textno[i].Alfa);
	//�|���S���̏��ݒ�
	SetPolygonPos(pos.x, pos.y);
	SetPolygonSize(size.x, size.y);
	SetPolygonAngle(textno[i].g_Angle);
	//degree(�f�O���[)�l
	SetPolygonUV(textno[i].g_TexCoord.x, textno[i].g_TexCoord.y);		  //�����UV���W
	SetPolygonFrameSize(textno[i].g_TexFrameSize.x, textno[i].g_TexFrameSize.y);  //�����c��
	SetPolygonTexture(textno[i].g_pTexture);	  //�e�N�X�`���w��

	// �|���S���̕`�揈��
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	SetPolygonAlpha(1.0f);
}