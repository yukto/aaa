//=============================================================================
//
// ���b�V�����ʏ��� [mesh.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"
#include "Camera.h"
#include "Light.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
enum ePrimitiveType {
	PT_UNDEFINED = 0,
	PT_POINT,
	PT_LINE,
	PT_LINESTRIP,
	PT_TRIANGLE,
	PT_TRIANGLESTRIP,

	MAX_PRIMITIVETYPE
};
enum eTranslucentType {
	TT_NOAFFECT = 0,	// �S��
	TT_OPACITYONLY,		// �s�����̂�
	TT_TRANSLUCENTONLY,	// �������̂�

	MAX_TRANSLUCENTTYPE
};

//**************************************
// �\���̒�`
//**************************************
typedef struct {
	XMFLOAT4	Diffuse;		// Diffuse color RGBA
	XMFLOAT4	Ambient;		// Ambient color RGB
	XMFLOAT4	Specular;		// Specular 'shininess'
	XMFLOAT4	Emissive;		// Emissive color RGB
	float		Power;			// Sharpness if specular highlight
} MATERIAL;

typedef struct {
	ID3D11Buffer* pVertexBuffer;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	ID3D11Buffer* pIndexBuffer;				// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	XMFLOAT4X4 mtxWorld;					// ���[���h�}�g���b�N�X
	XMFLOAT3 pos;							// �|���S���\���ʒu�̒��S���W
	XMFLOAT3 rot;							// �|���S���̉�]�p
	int nNumVertex;							// �����_��	
	int nNumIndex;							// ���C���f�b�N�X��

	XMFLOAT4X4 mtxTexture;					// �e�N�X�`�� �}�g���b�N�X
	ID3D11ShaderResourceView* pTexture;		// �e�N�X�`��

	ePrimitiveType primitiveType;			// �v���~�e�B�u�^

	MATERIAL* pMaterial;					// �}�e���A��
	float fAlpha;							// ���_�J���[���ŏ��l
} MESH;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMesh(void);
void UninitMesh(void);
void UpdateMesh(MESH* pMesh);
void DrawMesh(ID3D11DeviceContext* pDeviceContext, MESH* pMesh, int nTranslucntType = TT_NOAFFECT);
HRESULT MakeMeshVertex(ID3D11Device* pDevice, MESH* pMesh, VERTEX_3D vertexWk[], int indexWk[]);
void ReleaseMesh(MESH* pMesh);
