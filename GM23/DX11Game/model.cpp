//=============================================================================
//
// モデル処理 [model.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "model.h"
#include "sceneTitle.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define VALUE_MOVE		(1.0f)
#define VALUE_ROTATE	(5.0f)
#define MODEL_OCERO		"data/model/assistant/Standing Idle.fbx"
#define MODEL_SKYDOME1	"data/model/skydome/dome301.x"
#define MODEL_SKYDOME2	"data/model/skydome/dome308.x"
#define MODEL_SKYDOME3	"data/model/skydome/dome309.x"
#define MODEL_SKYDOME4	"data/model/skydome/dome312.x"
#define MODEL_SKYDOME5	"data/model/skydome/dome321.x"
#define MODEL_SKYDOME6	"data/model/assistant/Petting.fbx"
#define MODEL_NO		(7)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
static tModel				g_model[MODEL_NO];
static float				vel;
static bool					RotationSwitch;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModel(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	for (int i = 0; i < MODEL_NO; i++)
	{
		// 位置・回転・スケールの初期設定
		g_model[i].posModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_model[i].rotModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_model[i].velModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_model[i].sclModel = XMFLOAT3(1.0f, 1.0f, 1.0f);
		g_model[i].nState = 1;
		if(i > 1)g_model[i].nState = 0;
		g_model[i].Anime = 0;
		// ワールドマトリックスの初期化
		XMMATRIX mtxWorld;
		mtxWorld = XMMatrixIdentity();
		XMStoreFloat4x4(&g_model[i].mtxWorld, mtxWorld);
		// モデルデータの読み込み
	}
	g_model[0].posModel = XMFLOAT3(-50.0f, 0.0f, 0.0f);
	g_model[0].rotModel = XMFLOAT3(0.0f, -20.0f, 0.0f);
	vel = 0.1f;
	RotationSwitch = false;
	hr = g_model[0].model.Load(pDevice, pDeviceContext, MODEL_OCERO);
	hr = g_model[1].model.Load(pDevice, pDeviceContext, MODEL_SKYDOME1);
	hr = g_model[2].model.Load(pDevice, pDeviceContext, MODEL_SKYDOME2);
	hr = g_model[3].model.Load(pDevice, pDeviceContext, MODEL_SKYDOME3);
	hr = g_model[4].model.Load(pDevice, pDeviceContext, MODEL_SKYDOME4);
	hr = g_model[5].model.Load(pDevice, pDeviceContext, MODEL_SKYDOME5);
	hr = g_model[6].model.Load(pDevice, pDeviceContext, MODEL_SKYDOME6);
	return hr;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	// モデルの解放
	for (int i = 0; i < MODEL_NO; i++)
	{
		g_model[i].model.Release();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{
	for (int i = 0; i < MODEL_NO; i++)
	{
		if (g_model[i].nState == 0)continue;
		if (i > 0 && i < 6)
		{
			g_model[i].rotModel.y += vel;
			if (RotationSwitch)vel *= 1.1f;
			if (vel > 10.0f)
			{
				RotationSwitch = false;
				g_model[i].nState = 0;
				g_model[GetMenuNo()].nState = 1;
			}
			if (!RotationSwitch && vel > 0.1f)vel /= 1.1f;
		}
		XMMATRIX mtxWorld, mtxRot, mtxScl,
			mtxTranslate;

		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(g_model[i].sclModel.x, g_model[i].sclModel.y, g_model[i].sclModel.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_model[i].rotModel.x), XMConvertToRadians(g_model[i].rotModel.y), XMConvertToRadians(g_model[i].rotModel.z));
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_model[i].posModel.x, g_model[i].posModel.y, g_model[i].posModel.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックス設定
		XMStoreFloat4x4(&g_model[i].mtxWorld, mtxWorld);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	for (int i = 0; i < MODEL_NO; i++)
	{
		if (g_model[i].nState == 0)continue;
		// モデル表示
		g_model[i].model.Draw(pDeviceContext, g_model[i].mtxWorld);
	}
}

void RotationSwitchOn()
{
	if(vel <= 0.1f)RotationSwitch = true;
}

bool GetRotationSwitch()
{
	if (!RotationSwitch && vel <= 0.1f)return true;
	return false;
}

void AnimeSwitch(int no,int no2)
{
	g_model[no].nState = 0;
	g_model[no2].nState = 1;
}