//=============================================================================
//
// ���b�V�����ʏ��� [mesh.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "mesh.h"
#include "Shader.h"
#include "Texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define M_DIFFUSE		XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
#define M_SPECULAR		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)
#define M_AMBIENT		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_EMISSIVE		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �V�F�[�_�ɓn���l
struct SHADER_GLOBAL {
	XMMATRIX	mWVP;		// ���[���h�~�r���[�~�ˉe�s��(�]�u�s��)
	XMMATRIX	mW;			// ���[���h�s��(�]�u�s��)
	XMMATRIX	mTex;		// �e�N�X�`���s��(�]�u�s��)
};
struct SHADER_GLOBAL2 {
	XMVECTOR	vEye;		// ���_���W
	// ����
	XMVECTOR	vLightDir;	// ��������
	XMVECTOR	vLa;		// �����F(�A���r�G���g)
	XMVECTOR	vLd;		// �����F(�f�B�t���[�Y)
	XMVECTOR	vLs;		// �����F(�X�y�L����)
	// �}�e���A��
	XMVECTOR	vAmbient;	// �A���r�G���g�F(+�e�N�X�`���L��)
	XMVECTOR	vDiffuse;	// �f�B�t���[�Y�F
	XMVECTOR	vSpecular;	// �X�y�L�����F(+�X�y�L�������x)
	XMVECTOR	vEmissive;	// �G�~�b�V�u�F
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer*				g_pConstantBuffer[2];	// �萔�o�b�t�@
static ID3D11SamplerState*			g_pSamplerState;		// �e�N�X�`�� �T���v��
static ID3D11VertexShader*			g_pVertexShader;		// ���_�V�F�[�_
static ID3D11InputLayout*			g_pInputLayout;			// ���_�t�H�[�}�b�g
static ID3D11PixelShader*			g_pPixelShader;			// �s�N�Z���V�F�[�_

// �}�e���A��
static MATERIAL						g_material;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMesh(void)
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr;

	// �V�F�[�_������
	static const D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	hr = LoadShader("Vertex", "Pixel", &g_pVertexShader, &g_pInputLayout, &g_pPixelShader, layout, _countof(layout));
	if (FAILED(hr)) {
		return hr;
	}

	// �萔�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SHADER_GLOBAL);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = pDevice->CreateBuffer(&bd, nullptr, &g_pConstantBuffer[0]);
	if (FAILED(hr)) return hr;
	bd.ByteWidth = sizeof(SHADER_GLOBAL2);
	hr = pDevice->CreateBuffer(&bd, nullptr, &g_pConstantBuffer[1]);
	if (FAILED(hr)) return hr;

	// �e�N�X�`�� �T���v������
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = pDevice->CreateSamplerState(&sd, &g_pSamplerState);
	if (FAILED(hr)) {
		return hr;
	}

	// �}�e���A���̏����ݒ�
	g_material.Diffuse = M_DIFFUSE;
	g_material.Ambient = M_AMBIENT;
	g_material.Specular = M_SPECULAR;
	g_material.Power = 0.0f;
	g_material.Emissive = M_EMISSIVE;

	return hr;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMesh(void)
{
	// �e�N�X�`�� �T���v���̊J��
	SAFE_RELEASE(g_pSamplerState);
	// �萔�o�b�t�@�̉��
	for (int i = 0; i < _countof(g_pConstantBuffer); ++i) {
		SAFE_RELEASE(g_pConstantBuffer[i]);
	}
	// �s�N�Z���V�F�[�_���
	SAFE_RELEASE(g_pPixelShader);
	// ���_�t�H�[�}�b�g���
	SAFE_RELEASE(g_pInputLayout);
	// ���_�V�F�[�_���
	SAFE_RELEASE(g_pVertexShader);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMesh(MESH* pMesh)
{
	XMMATRIX mtxWorld, mtxRot, mtxTranslate;

	if (!pMesh) return;

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();

	// ��]�𔽉f
	mtxRot = XMMatrixRotationRollPitchYaw(
		XMConvertToRadians(pMesh->rot.x), XMConvertToRadians(pMesh->rot.y),
		XMConvertToRadians(pMesh->rot.z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(pMesh->pos.x, pMesh->pos.y, pMesh->pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	XMStoreFloat4x4(&pMesh->mtxWorld, mtxWorld);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMesh(ID3D11DeviceContext* pDeviceContext, MESH* pMesh, int nTranslucntType)
{
	MATERIAL* pMaterial = pMesh->pMaterial;
	if (!pMaterial) pMaterial = &g_material;
	switch (nTranslucntType) {
	case TT_OPACITYONLY:		// �s�����̂�
		if (pMaterial->Diffuse.w < 1.0f || pMesh->fAlpha < 1.0f) {
			return;
		}
		break;
	case TT_TRANSLUCENTONLY:	// �������̂�
		if (pMaterial->Diffuse.w >= 1.0f && pMesh->fAlpha >= 1.0f) {
			return;
		}
		break;
	default:					// �s�����x�ŋ�ʂ��Ȃ�
		break;
	}
	// �V�F�[�_�ݒ�
	pDeviceContext->VSSetShader(g_pVertexShader, nullptr, 0);
	pDeviceContext->PSSetShader(g_pPixelShader, nullptr, 0);
	pDeviceContext->IASetInputLayout(g_pInputLayout);

	// ���_�o�b�t�@���Z�b�g
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &pMesh->pVertexBuffer, &stride, &offset);
	// �C���f�b�N�X�o�b�t�@���Z�b�g
	pDeviceContext->IASetIndexBuffer(pMesh->pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	pDeviceContext->PSSetSamplers(0, 1, &g_pSamplerState);
	pDeviceContext->PSSetShaderResources(0, 1, &pMesh->pTexture);

	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&pMesh->mtxWorld);
	cb.mWVP = XMMatrixTranspose(mtxWorld * XMLoadFloat4x4(&GetCamera()->GetViewMatrix()) * XMLoadFloat4x4(&GetCamera()->GetProjMatrix()));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&pMesh->mtxTexture));
	pDeviceContext->UpdateSubresource(g_pConstantBuffer[0], 0, nullptr, &cb, 0, 0);
	pDeviceContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer[0]);
	SHADER_GLOBAL2 cb2;
	cb2.vEye = XMLoadFloat3(&GetCamera()->GetPos());
	cb2.vLightDir = XMLoadFloat3(&GetLight()->GetDir());
	cb2.vLa = XMLoadFloat4(&GetLight()->GetAmbient());
	cb2.vLd = XMLoadFloat4(&GetLight()->GetDiffuse());
	cb2.vLs = XMLoadFloat4(&GetLight()->GetSpecular());
	cb2.vDiffuse = XMLoadFloat4(&pMaterial->Diffuse);
	cb2.vAmbient = XMVectorSet(pMaterial->Ambient.x, pMaterial->Ambient.y, pMaterial->Ambient.z, (pMesh->pTexture != nullptr) ? 1.f : 0.f);
	cb2.vSpecular = XMVectorSet(pMaterial->Specular.x, pMaterial->Specular.y, pMaterial->Specular.z, pMaterial->Power);
	cb2.vEmissive = XMLoadFloat4(&pMaterial->Emissive);
	pDeviceContext->UpdateSubresource(g_pConstantBuffer[1], 0, nullptr, &cb2, 0, 0);
	pDeviceContext->PSSetConstantBuffers(1, 1, &g_pConstantBuffer[1]);

	// �v���~�e�B�u�`����Z�b�g
	static const D3D11_PRIMITIVE_TOPOLOGY pt[] = {
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,	// 0�Ȃ�O�p�`�X�g���b�v
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	};
	pDeviceContext->IASetPrimitiveTopology(pt[pMesh->primitiveType]);

	// �|���S���̕`��
	pDeviceContext->DrawIndexed(pMesh->nNumIndex, 0, 0);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeMeshVertex(ID3D11Device* pDevice, MESH* pMesh, VERTEX_3D vertexWk[], int indexWk[])
{
	pMesh->fAlpha = 1.0f;
	for (int i = 0; i < pMesh->nNumVertex; ++i) {
		if (pMesh->fAlpha > vertexWk[i].diffuse.w) {
			pMesh->fAlpha = vertexWk[i].diffuse.w;
		}
	}

	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(VERTEX_3D) * pMesh->nNumVertex;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertexWk;
	HRESULT hr = pDevice->CreateBuffer(&vbd, &initData, &pMesh->pVertexBuffer);
	if (FAILED(hr)) {
		return hr;
	}

	CD3D11_BUFFER_DESC ibd(pMesh->nNumIndex * sizeof(int), D3D11_BIND_INDEX_BUFFER);
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = indexWk;
	hr = pDevice->CreateBuffer(&ibd, &initData, &pMesh->pIndexBuffer);

	return hr;
}

//=============================================================================
// ���b�V�����
//=============================================================================
void ReleaseMesh(MESH* pMesh)
{
	if (!pMesh) return;
	// �e�N�X�`�����
	SAFE_RELEASE(pMesh->pTexture);
	// ���_�o�b�t�@���
	SAFE_RELEASE(pMesh->pVertexBuffer);
	// �C���f�b�N�X �o�b�t�@���
	SAFE_RELEASE(pMesh->pIndexBuffer);
}


