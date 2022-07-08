//=============================================================================
//
// 弾処理 [billboard.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "billboard.h"
#include "Shader.h"
#include "Texture.h"
#include "mesh.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_BILLBOARD	L"data/texture/monster/dodai2.png"	// テクスチャ
#define TEXTURE_BILLBOARD1	L"data/texture/monster/card.png"	// テクスチャ
#define TEXTURE_BILLBOARD2	L"data/texture/monster/かめ.png"
#define TEXTURE_BILLBOARD3	L"data/texture/monster/クリオネ.png"
#define TEXTURE_BILLBOARD4	L"data/texture/monster/こけ.png"
#define TEXTURE_BILLBOARD5	L"data/texture/monster/こけー.png"
#define TEXTURE_BILLBOARD6	L"data/texture/monster/ゴジラ.png"
#define TEXTURE_BILLBOARD7	L"data/texture/monster/スチーム.png"
#define TEXTURE_BILLBOARD8	L"data/texture/monster/スライム.png"
#define TEXTURE_BILLBOARD9	L"data/texture/monster/どら.png"
#define TEXTURE_BILLBOARD10	L"data/texture/monster/にく.png"
#define TEXTURE_BILLBOARD11	L"data/texture/monster/にょろ.png"
#define TEXTURE_BILLBOARD12	L"data/texture/monster/ばーん.png"
#define TEXTURE_BILLBOARD13	L"data/texture/monster/ばーん1.png"
#define TEXTURE_BILLBOARD14	L"data/texture/monster/ブラックタイガー.png"
#define TEXTURE_BILLBOARD15	L"data/texture/monster/ミミック2.png"
#define TEXTURE_BILLBOARD16	L"data/texture/monster/メガネ.png"
#define TEXTURE_BILLBOARD17	L"data/texture/monster/らいがー.png"
#define TEXTURE_BILLBOARD18	L"data/texture/monster/人玉.png"
#define TEXTURE_BILLBOARD19	L"data/texture/monster/石.png"
#define TEXTURE_BILLBOARD20	L"data/texture/monster/妖精.png"
#define TEXTURE_BILLBOARD21	L"data/texture/monster/妖精サンプル.png"

#define M_DIFFUSE		XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
#define M_SPECULAR		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)
#define M_AMBIENT		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_EMISSIVE		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)

#define BILLBOARD_SPEED			(5.0f)
#define BILLBOARD_RADIUS		(10.0f)
#define MAXBILLBOARDTEXT		(6)

//*****************************************************************************
// 構造体定義
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
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBillboard(ID3D11Device* pDevice, int no);
void SetTextureBillboard(const tBillboard* pExplosion, int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static MESH		g_mesh[MAXBILLBOARDTEXT];		// メッシュ情報
static MATERIAL	g_material[MAXBILLBOARDTEXT];	// マテリアル情報
static tBillboard g_billboard[MAX_BILLBOARD];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBillboard(void)
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr;
	HWND hWnd = GetMainWnd();

	for (int i = 0; i < MAXBILLBOARDTEXT; i++)
	{
		// マテリアルの初期設定
		g_material[i].Diffuse = M_DIFFUSE;
		g_material[i].Ambient = M_AMBIENT;
		g_material[i].Specular = M_SPECULAR;
		g_material[i].Power = 50.0f;
		g_material[i].Emissive = M_EMISSIVE;
		g_mesh[i].pMaterial = &g_material[i];
	}

	// テクスチャの読み込み
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
			_T("弾テクスチャ読み込みエラー"),
			_T("Error"),
			MB_OK | MB_ICONSTOP);
		return hr;
	}
	for (int i = 0; i < MAXBILLBOARDTEXT; i++)
	{
		XMStoreFloat4x4(&g_mesh[i].mtxTexture,
			XMMatrixIdentity());

		// ワールドマトリクス初期化
		XMStoreFloat4x4(&g_mesh[i].mtxWorld,
			XMMatrixIdentity());
		// 頂点情報の作成
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
// 終了処理
//=============================================================================
void UninitBillboard(void)
{
	tBillboard* pBillboard = g_billboard;
	for (int i = 0; i < MAX_BILLBOARD;
		++i, ++pBillboard)
	{
		if (pBillboard->nState == 0) continue;
		pBillboard->nState = 0;
		// 影との関連を切る
		pBillboard->nShadowIdx = -1;
	}

	// メッシュ解放
	for (int i = 0; i < MAXBILLBOARDTEXT; i++)
	{
		ReleaseMesh(&g_mesh[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBillboard(void)
{
	// 更新処理
	tBillboard* pBillboard = g_billboard;
	for (int i = 0; i < MAX_BILLBOARD;
		++i, ++pBillboard)
	{
		if (pBillboard->nState == 0) continue;
		// 位置の更新
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBillboard()
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// 合成設定
	SetBlendState(BS_ALPHABLEND);
	XMFLOAT4X4 mView = GetCamera()->GetViewMatrix();
	tBillboard* pBillboard = g_billboard;
	for (int i = 0; i < MAX_BILLBOARD; ++i, ++pBillboard)
	{	//出ていない弾は発射しない
		if (pBillboard->nState == 0)continue;
		//ビュー行列の回転成分の転置行列を設定
		g_mesh[pBillboard->TextureNo].mtxWorld._11 = mView._11;
		g_mesh[pBillboard->TextureNo].mtxWorld._12 = mView._21;
		g_mesh[pBillboard->TextureNo].mtxWorld._13 = mView._31;
		g_mesh[pBillboard->TextureNo].mtxWorld._21 = mView._12;
		g_mesh[pBillboard->TextureNo].mtxWorld._22 = mView._22;
		g_mesh[pBillboard->TextureNo].mtxWorld._23 = mView._32;
		g_mesh[pBillboard->TextureNo].mtxWorld._31 = mView._13;
		g_mesh[pBillboard->TextureNo].mtxWorld._32 = mView._23;
		g_mesh[pBillboard->TextureNo].mtxWorld._33 = mView._33;

		//拡大縮小
		XMMATRIX mtxScale = XMMatrixScaling(BILLBOARD_RADIUS, BILLBOARD_RADIUS, BILLBOARD_RADIUS);
		XMMATRIX mtxRot;
		mtxRot = XMLoadFloat4x4(&g_mesh[pBillboard->TextureNo].mtxWorld);
		mtxRot = XMMatrixMultiply(mtxRot, mtxScale);
		XMStoreFloat4x4(&g_mesh[pBillboard->TextureNo].mtxWorld, mtxRot);

		//位置を反映
		g_mesh[pBillboard->TextureNo].mtxWorld._41 = pBillboard->pos.x;
		g_mesh[pBillboard->TextureNo].mtxWorld._42 = pBillboard->pos.y;
		g_mesh[pBillboard->TextureNo].mtxWorld._43 = pBillboard->pos.z;

		SetTextureBillboard(pBillboard, i);

		DrawMesh(pDeviceContext, &g_mesh[pBillboard->TextureNo]);
	}

	// もとに戻す
	SetBlendState(BS_NONE);
}

// 弾の作成
int FireBillboard(XMFLOAT3 pos, XMFLOAT3 dir, int no)
{
	tBillboard* pBillboard = g_billboard;
	for (int i = 0; i < MAX_BILLBOARD; ++i, ++pBillboard)
	{	// 出現している弾はスルー
		if (pBillboard->nState > 0) continue;

		pBillboard->pos = pos;
		pBillboard->vel.x = dir.x * BILLBOARD_SPEED;
		pBillboard->vel.y = dir.y * BILLBOARD_SPEED;
		pBillboard->vel.z = dir.z * BILLBOARD_SPEED;
		pBillboard->nState = 1;	// 出現
		pBillboard->nShadowIdx = -1;
		pBillboard->TextureNo = no;
		return i;	// 番号を返す
	}

	return -1;	// 見つからなかった
}

HRESULT MakeVertexBillboard(ID3D11Device* pDevice, int no)
{
	VERTEX_3D vertexWk[NUM_VERTEX]; //作業用頂点情報
	int		  indexWk[NUM_VERTEX];	//作業用インデックス

	// 頂点座標の設定
	g_mesh[no].nNumVertex = NUM_VERTEX;
	vertexWk[0].vtx = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[1].vtx = XMFLOAT3(2.0f, 1.0f, 0.0f);
	vertexWk[2].vtx = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertexWk[3].vtx = XMFLOAT3(2.0f, -1.0f, 0.0f);

	// ディフューズの設定
	vertexWk[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// 法線ベクトルの設定
	vertexWk[0].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertexWk[1].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertexWk[2].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertexWk[3].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);

	// テクスチャ座標の設定
	vertexWk[0].tex = XMFLOAT2(1.0f, 0.0f);
	vertexWk[1].tex = XMFLOAT2(0.0f, 0.0f);
	vertexWk[2].tex = XMFLOAT2(1.0f, 1.0f);
	vertexWk[3].tex = XMFLOAT2(0.0f, 1.0f);

	// インデックス配列の設定
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

	//テクスチャマトリクスの初期化
	mtxTexture = XMMatrixIdentity();
	//スケールを反映
	mtxScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);	//横に８個　縦に１個
	mtxTexture = XMMatrixMultiply(mtxTexture, mtxScale);

	//移動を反映
	mtxTranslate = XMMatrixTranslation(
		1.0f, 1.0f, 0.0f);
	//今回は８が横、１が縦の数
	mtxTexture = XMMatrixMultiply(mtxTexture, mtxTranslate);
	XMStoreFloat4x4(&g_mesh[no].mtxTexture, mtxTexture);
}