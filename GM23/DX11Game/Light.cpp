// light.cpp
#include "Light.h"

using namespace DirectX;

// マクロ定義
#define LIGHT0_DIRECTION	XMFLOAT3(0.0f, -0.01f, 0.1f)
#define LIGHT0_DIFFUSE		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
#define LIGHT0_AMBIENT		XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
#define LIGHT0_SPECULAR		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)

// グローバル変数
static CLight g_light;

// コンストラクタ
CLight::CLight()
{
	Init();
}

// 初期化
void CLight::Init()
{
	XMFLOAT3 vDir = LIGHT0_DIRECTION;
	XMStoreFloat3(&m_direction, XMVector3Normalize(XMLoadFloat3(&vDir)));
	m_diffuse = LIGHT0_DIFFUSE;
	m_ambient = LIGHT0_AMBIENT;
	m_specular = LIGHT0_SPECULAR;
	m_bEnable = true;

}

void CLight::Update()
{
}

// 光源方向取得
XMFLOAT3& CLight::GetDir()
{
	if (m_bEnable) return m_direction;
	static XMFLOAT3 off(0.0f, 0.0f, 0.0f);
	return off;
}


CLight * GetLight()
{
	return &g_light;
}
