//=============================================================================
//
// DirectX11�x�[�X [explosion.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================

//*******�C���N���[�h************
#include "HS_effect.h"
#include <time.h>
#define EXPLOSION_TEXTURENAME4		_T("data/texture/HS/water.png")		// �|���S���ɕ\��������摜

//================================
//			������
//================================
HRESULT GameEffect::HS_InitExplosion(char* text,XMFLOAT2 size,XMFLOAT2 frame,int no)
{
	HRESULT hr = S_OK;

	// �e�N�X�`���ǂݍ���
	ID3D11Device*	pDevice = GetDevice();
	hr = CreateTextureFromFile(pDevice, text, &g_pTexture);

	EXPLOSION_FRAME = frame;

	for (int i = 0; i < (int)frame.x * (int)frame.y; i++)
	{
		g_animPat[0][i].nPatNo = i;
		g_animPat[0][i].nCount = no;
	}

	//�p�����[�^�̏�����
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		g_Explosion[i].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_Explosion[i].Size = XMFLOAT2(size.x, size.y);
		g_Explosion[i].Angle = 0.0f;
		g_Explosion[i].vel = XMFLOAT2(0.0f, 0.0f);
		g_Explosion[i].bUse = false;	//�ŏ��͖��g�p���
		g_Explosion[i].Scale = XMFLOAT2(1.0f, 1.0f);			// �g��k��
		g_Explosion[i].nDir = 0;		// ����
		g_Explosion[i].nAnimNo = 0;		// �\�����No.
		g_Explosion[i].nCount = g_animPat[0][g_Explosion[i].nAnimNo].nCount;			// �c��t���[����
	}
	return hr;
}

//================================
//			�I��
//================================
void GameEffect::HS_UninitExplosion()
{
	// �e�N�X�`����ЂÂ�
	SAFE_RELEASE(g_pTexture);
}


//================================
//			�X�V
//================================
void GameEffect::HS_UpdateExplosion(void)
{
		//�G�̔z������Ԃɉ񂵂āA�X�V�i�ړ��j������
		for (int i = 0; i < MAX_EXPLOSION; i++)
		{
			//�o�Ă��Ȃ��G�͏������Ȃ�
			if (g_Explosion[i].bUse == false)
			{
				continue;
			}

			//�ړ�
			//�A�j���[�V�������̍X�V
			g_Explosion[i].nCount--;		//�c��J�E���g�����炷
			if (g_Explosion[i].nCount <= 0)
			{
				g_Explosion[i].nAnimNo++;		//���̊G�ɐi�߂�
				if (g_animPat[g_Explosion[i].nDir][g_Explosion[i].nAnimNo].nPatNo < 0)
				{		//�ԕ����Q�Ƃ�����
					g_Explosion[i].bUse = false;	//�擪�ɖ߂�
				}
				//�J�E���^�����̊G�̕\���t���[�����ɐݒ�
				g_Explosion[i].nCount = g_animPat[g_Explosion[i].nDir][g_Explosion[i].nAnimNo].nCount;
			}
		}
}


//================================
//			�`��
//================================
void GameEffect::HS_DrawExplosion()
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		//�����˂̓G�͕\�����Ȃ�
		if (g_Explosion[i].bUse == false)
		{
			continue;
		}

		//�|���S���̏��ݒ�		����
		SetPolygonAngle(g_Explosion[i].Angle);						//degree(�f�O���[)�l(0~360��)	
		SetPolygonPos(g_Explosion[i].Position.x, g_Explosion[i].Position.y);
		SetPolygonSize(g_Explosion[i].Size.x, g_Explosion[i].Size.y);
													//����radian(���W�A��)�l(0~2��)

		SetPolygonFrameSize(1.0f / EXPLOSION_FRAME.x, 1.0f / EXPLOSION_FRAME.y);// �����c��
		int u = g_animPat[g_Explosion[i].nDir][g_Explosion[i].nAnimNo].nPatNo % (int)EXPLOSION_FRAME.x;
		int v = g_animPat[g_Explosion[i].nDir][g_Explosion[i].nAnimNo].nPatNo / (int)EXPLOSION_FRAME.x;
		SetPolygonUV(u / EXPLOSION_FRAME.x, v / EXPLOSION_FRAME.y);	// �����UV���W
		SetPolygonTexture(g_pTexture);// �e�N�X�`���w��


		// �|���S���̕`�揈��
		ID3D11DeviceContext*	pDeviceContext = GetDeviceContext();
		DrawPolygon(pDeviceContext);
		SetPolygonAngle(0.0f);
	}
}

//�G�̔���
//pos : �w�肳�ꂽ�ꏊ
void GameEffect::HS_SetExplosion(XMFLOAT3 pos, bool bAngle)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		//���˂���Ă���G�͔��˂ł��Ȃ�
		if (g_Explosion[i].bUse == true)
		{
			continue;
		}

		g_Explosion[i].bUse = true;		//���ˏ��
		g_Explosion[i].Position = pos;
		if(bAngle)g_Explosion[i].Angle = (float)(rand() % 360);
		else g_Explosion[i].Angle = 0.0f;
		g_Explosion[i].nAnimNo = 0;
		g_Explosion[i].nCount = g_animPat[0][g_Explosion[i].nAnimNo].nCount;
		g_Explosion[i].nDir = 0;

		break;
	}
}
//
//void GameEffect::HS_BreakExplosion(int no)
//{
//	g_Explosion[no].bUse = false;
//}