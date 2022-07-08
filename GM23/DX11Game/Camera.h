// Camera.h
#pragma once
#include "main.h"

class CCamera
{
private:
	DirectX::XMFLOAT3 m_vPos;		// ���_
	DirectX::XMFLOAT3 m_vTarget;	// �����_
	DirectX::XMFLOAT3 m_vUp;		// ����x�N�g��

	float m_fAspectRatio;			// �c����
	float m_fFovY;					// ����p(Degree)
	float m_fNearZ;					// �O���N���b�v����
	float m_fFarZ;					// ����N���b�v����

	DirectX::XMFLOAT4X4 m_mtxWorld;	// ���[���h �}�g���b�N�X
	DirectX::XMFLOAT4X4 m_mtxView;	// �r���[ �}�g���b�N�X
	DirectX::XMFLOAT4X4 m_mtxProj;	// �v���W�F�N�V���� �}�g���b�N�X

	XMFLOAT3 m_vAngle;		// �J�����̊p�x
	float m_fLengthInterval;// �J�����̎��_�ƒ����_�̋���

public:
	CCamera();

	void Init();
	void Update();

	void SetPos(DirectX::XMFLOAT3& vPos) { m_vPos = vPos; }
	DirectX::XMFLOAT3& GetPos() { return m_vPos; }
	void SetPos(float x, float y, float z) { m_vPos.x = x, m_vPos.y = y, m_vPos.z = z; }
	void SetTarget(DirectX::XMFLOAT3& vTarget) { m_vTarget = vTarget; }
	void SetTarget(float x, float y, float z) { m_vTarget.x = x, m_vTarget.y = y, m_vTarget.z = z; }
	void SetUpVector(DirectX::XMFLOAT3& vUp) { m_vUp = vUp; }
	void SetUpVector(float x, float y, float z) { m_vUp.x = x, m_vUp.y = y, m_vUp.z = z; }
	void SetWorldMatrix(DirectX::XMFLOAT4X4& mtxWorld);
	DirectX::XMFLOAT4X4& GetWorldMatrix() { return m_mtxWorld; }
	DirectX::XMFLOAT4X4& CalcWorldMatrix();
	void SetFovY(float fFovY) { m_fFovY = fFovY; }
	void SetAspectRatio(float fAspect) { m_fAspectRatio = fAspect; }
	void SetRangeZ(float fNearZ, float fFarZ) { m_fNearZ = fNearZ, m_fFarZ = fFarZ; }
	DirectX::XMFLOAT4X4& GetViewMatrix() { return m_mtxView; }
	DirectX::XMFLOAT4X4& GetProjMatrix() { return m_mtxProj; }
	void UpdateMatrix();
	DirectX::XMFLOAT3& GetAngle() { return m_vAngle; }
};

CCamera* GetCamera();
