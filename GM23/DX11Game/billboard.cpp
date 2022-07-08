//=============================================================================
//
// �e���� [billboard.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "billboard.h"
#include "Shader.h"
#include "Texture.h"
#include "mesh.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_BILLBOARD	L"data/texture/monster/dodai2.png"	// �e�N�X�`��
#define TEXTURE_BILLBOARD1	L"data/texture/monster/card.png"	// �e�N�X�`��
#define TEXTURE_BILLBOARD2	L"data/texture/monster/����.png"
#define TEXTURE_BILLBOARD3	L"data/texture/monster/�N���I�l.png"
#define TEXTURE_BILLBOARD4	L"data/texture/monster/����.png"
#define TEXTURE_BILLBOARD5	L"data/texture/monster/�����[.png"
#define TEXTURE_BILLBOARD6	L"data/texture/monster/�S�W��.png"
#define TEXTURE_BILLBOARD7	L"data/texture/monster/�X�`�[��.png"
#define TEXTURE_BILLBOARD8	L"data/texture/monster/�X���C��.png"
#define TEXTURE_BILLBOARD9	L"data/texture/monster/�ǂ�.png"
#define TEXTURE_BILLBOARD10	L"data/texture/monster/�ɂ�.png"
#define TEXTURE_BILLBOARD11	L"data/texture/monster/�ɂ��.png"
#define TEXTURE_BILLBOARD12	L"data/texture/monster/�΁[��.png"
#define TEXTURE_BILLBOARD13	L"data/texture/monster/�΁[��1.png"
#define TEXTURE_BILLBOARD14	L"data/texture/monster/�u���b�N�^�C�K�[.png"
#define TEXTURE_BILLBOARD15	L"data/texture/monster/�~�~�b�N2.png"
#define TEXTURE_BILLBOARD16	L"data/texture/monster/���K�l.png"
#define TEXTURE_BILLBOARD17	L"data/texture/monster/�炢���[.png"
#define TEXTURE_BILLBOARD18	L"data/texture/monster/�l��.png"
#define TEXTURE_BILLBOARD19	L"data/texture/monster/��.png"
#define TEXTURE_BILLBOARD20	L"data/texture/monster/�d��.png"
#define TEXTURE_BILLBOARD21	L"data/texture/monster/�d���T���v��.png"

#define M_DIFFUSE		XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
#define M_SPECULAR		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)
#define M_AMBIENT		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_EMISSIVE		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)

#define BILLBOARD_SPEED			(5.0f)
#define BILLBOARD_RADIUS		(10.0f)
#define MAXBILLBOARDTEXT		(6)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct _tBillboard
{
	int				nState;
	XMFLOAT3		pos;
	XMFLOAT3		vel;
	int				nShadowIdx;
	int				TextureNo;
}tBillboard;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBillboard(ID3D11Device* pDevice, int no);
void SetTextureBillboard(const tBillboard* pExplosion, int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static MESH		g_mesh[MAXBILLBOARDTEXT];		// ���b�V�����
static MATERIAL	g_material[MAXBILLBOARDTEXT];	// �}�e���A�����
static tBillboard g_billboard[MAX_BILLBOARD];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBillboard(void)
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr;
	HWND hWnd = GetMainWnd();

	for (int i = 0; i < MAXBILLBOARDTEXT; i++)
	{
		// �}�e���A���̏����ݒ�
		g_material[i].Diffuse = M_DIFFUSE;
		g_material[i].Ambient = M_AMBIENT;
		g_material[i].Specular = M_SPECULAR;
		g_material[i].Power = 50.0f;
		g_material[i].Emissive = M_EMISSIVE;
		g_mesh[i].pMaterial = &g_material[i];
	}

	// �e�N�X�`���̓ǂݍ���
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD, &g_mesh[0].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD, &g_mesh[1].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD4, &g_mesh[2].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD5, &g_mesh[3].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD1, &g_mesh[4].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD1, &g_mesh[5].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD6, &g_mesh[6].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD7, &g_mesh[7].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD8, &g_mesh[8].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD9, &g_mesh[9].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD10, &g_mesh[10].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD11, &g_mesh[11].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD12, &g_mesh[12].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD13, &g_mesh[13].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD14, &g_mesh[14].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD15, &g_mesh[15].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD16, &g_mesh[16].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD17, &g_mesh[17].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD18, &g_mesh[18].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD19, &g_mesh[19].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD20, &g_mesh[20].pTexture);
	hr = CreateTextureFromFile(pDevice, TEXTURE_BILLBOARD21, &g_mesh[21].pTexture);
	if (FAILED(hr))
	{
		MessageBox(hWnd,
			_T("�e�e�N�X�`���ǂݍ��݃G���["),
			_T("Error"),
			MB_OK | MB_ICONSTOP);
		return hr;
	}
	for (int i = 0; i < MAXBILLBOARDTEXT; i++)
	{
		XMStoreFloat4x4(&g_mesh[i].mtxTexture,
			XMMatrixIdentity());

		// ���[���h�}�g���N�X������
		XMStoreFloat4x4(&g_mesh[i].mtxWorld,
			XMMatrixIdentity());
		// ���_���̍쐬
		hr = MakeVertexBillboard(pDevice, i);
	}
	for (int i = 0; i < MAX_BILLBOARD; i++)
	{
		g_billboard[i].nShadowIdx = -1;
		if(i < 2)FireBillboard(XMFLOAT3(-100 + 200 * (i % 2), 100, 0), XMFLOAT3(0, 0, 0), i);
		else if (i < 4)FireBillboard(XMFLOAT3(-100 + 200 * (i % 2), 120, 0), XMFLOAT3(0, 0, 0), i);
		else FireBillboard(XMFLOAT3(-100 + 200 * (i % 2), 120, 0), XMFLOAT3(0, 0, 0), i);
	}
	return hr;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBillboard(void)
{
	tBillboard* pBillboard = g_billboard;
	for (int i = 0; i < MAX_BILLBOARD;
		++i, ++pBillboard)
	{
		if (pBillboard->nState == 0) continue;
		pBillboard->nState = 0;
		// �e�Ƃ̊֘A��؂�
		pBillboard->nShadowIdx = -1;
	}

	// ���b�V�����
	for (int i = 0; i < MAXBILLBOARDTEXT; i++)
	{
		ReleaseMesh(&g_mesh[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBillboard(void)
{
	// �X�V����
	tBillboard* pBillboard = g_billboard;
	for (int i = 0; i < MAX_BILLBOARD;
		++i, ++pBillboard)
	{
		if (pBillboard->nState == 0) continue;
		// �ʒu�̍X�V
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBillboard()
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// �����ݒ�
	SetBlendState(BS_ALPHABLEND);
	XMFLOAT4X4 mView = GetCamera()->GetViewMatrix();
	tBillboard* pBillboard = g_billboard;
	for (int i = 0; i < MAX_BILLBOARD; ++i, ++pBillboard)
	{	//�o�Ă��Ȃ��e�͔��˂��Ȃ�
		if (pBillboard->nState == 0)continue;
		//�r���[�s��̉�]�����̓]�u�s���ݒ�
		g_mesh[pBillboard->TextureNo].mtxWorld._11 = mView._11;
		g_mesh[pBillboard->TextureNo].mtxWorld._12 = mView._21;
		g_mesh[pBillboard->TextureNo].mtxWorld._13 = mView._31;
		g_mesh[pBillboard->TextureNo].mtxWorld._21 = mView._12;
		g_mesh[pBillboard->TextureNo].mtxWorld._22 = mView._22;
		g_mesh[pBillboard->TextureNo].mtxWorld._23 = mView._32;
		g_mesh[pBillboard->TextureNo].mtxWorld._31 = mView._13;
		g_mesh[pBillboard->TextureNo].mtxWorld._32 = mView._23;
		g_mesh[pBillboard->TextureNo].mtxWorld._33 = mView._33;

		//�g��k��
		XMMATRIX mtxScale = XMMatrixScaling(BILLBOARD_RADIUS, BILLBOARD_RADIUS, BILLBOARD_RADIUS);
		XMMATRIX mtxRot;
		mtxRot = XMLoadFloat4x4(&g_mesh[pBillboard->TextureNo].mtxWorld);
		mtxRot = XMMatrixMultiply(mtxRot, mtxScale);
		XMStoreFloat4x4(&g_mesh[pBillboard->TextureNo].mtxWorld, mtxRot);

		//�ʒu�𔽉f
		g_mesh[pBillboard->TextureNo].mtxWorld._41 = pBillboard->pos.x;
		g_mesh[pBillboard->TextureNo].mtxWorld._42 = pBillboard->pos.y;
		g_mesh[pBillboard->TextureNo].mtxWorld._43 = pBillboard->pos.z;

		SetTextureBillboard(pBillboard, i);

		DrawMesh(pDeviceContext, &g_mesh[pBillboard->TextureNo]);
	}

	// ���Ƃɖ߂�
	SetBlendState(BS_NONE);
}

// �e�̍쐬
int FireBillboard(XMFLOAT3 pos, XMFLOAT3 dir, int no)
{
	tBillboard* pBillboard = g_billboard;
	for (int i = 0; i < MAX_BILLBOARD; ++i, ++pBillboard)
	{	// �o�����Ă���e�̓X���[
		if (pBillboard->nState > 0) continue;

		pBillboard->pos = pos;
		pBillboard->vel.x = dir.x * BILLBOARD_SPEED;
		pBillboard->vel.y = dir.y * BILLBOARD_SPEED;
		pBillboard->vel.z = dir.z * BILLBOARD_SPEED;
		pBillboard->nState = 1;	// �o��
		pBillboard->nShadowIdx = -1;
		pBillboard->TextureNo = no;
		return i;	// �ԍ���Ԃ�
	}

	return -1;	// ������Ȃ�����
}

HRESULT MakeVertexBillboard(ID3D11Device* pDevice, int no)
{
	VERTEX_3D vertexWk[NUM_VERTEX]; //��Ɨp���_���
	int		  indexWk[NUM_VERTEX];	//��Ɨp�C���f�b�N�X

	// ���_���W�̐ݒ�
	g_mesh[no].nNumVertex = NUM_VERTEX;
	vertexWk[0].vtx = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[1].vtx = XMFLOAT3(2.0f, 1.0f, 0.0f);
	vertexWk[2].vtx = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertexWk[3].vtx = XMFLOAT3(2.0f, -1.0f, 0.0f);

	// �f�B�t���[�Y�̐ݒ�
	vertexWk[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// �@���x�N�g���̐ݒ�
	vertexWk[0].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertexWk[1].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertexWk[2].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertexWk[3].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = XMFLOAT2(1.0f, 0.0f);
	vertexWk[1].tex = XMFLOAT2(0.0f, 0.0f);
	vertexWk[2].tex = XMFLOAT2(1.0f, 1.0f);
	vertexWk[3].tex = XMFLOAT2(0.0f, 1.0f);

	// �C���f�b�N�X�z��̐ݒ�
	g_mesh[no].nNumIndex = NUM_VERTEX;
	indexWk[0] = 0;
	indexWk[1] = 1;
	indexWk[2] = 2;
	indexWk[3] = 3;

	return MakeMeshVertex(pDevice, &g_mesh[no], vertexWk, indexWk);
}

void SetTextureBillboard(const tBillboard* pExplosion, int no)
{
	if (pExplosion == NULL) return;

	XMMATRIX mtxTexture, mtxScale, mtxTranslate;

	//�e�N�X�`���}�g���N�X�̏�����
	mtxTexture = XMMatrixIdentity();
	//�X�P�[���𔽉f
	mtxScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);	//���ɂW�@�c�ɂP��
	mtxTexture = XMMatrixMultiply(mtxTexture, mtxScale);

	//�ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(
		1.0f, 1.0f, 0.0f);
	//����͂W�����A�P���c�̐�
	mtxTexture = XMMatrixMultiply(mtxTexture, mtxTranslate);
	XMStoreFloat4x4(&g_mesh[no].mtxTexture, mtxTexture);
}