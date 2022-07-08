//=============================================================================
//
// ゲージ処理 [gauge.cpp]
//
//=============================================================================
#include "gauge.h"
#include "polygon.h"	// ポリゴン使用
#include "Texture.h"

// マクロ定義
#define GAUGE_SIZE_X	(200)
#define GAUGE_SIZE_Y	(25)
#define GAUGE_TEXTURENAME	_T("data/texture/game/gauge000.png")
#define GAUGE_TEXTURENAME1	_T("data/texture/game/gauge000.png")
#define GAUGE_TEXTURENAME2	_T("data/texture/game/gauge001.png")
#define GAUGE_TEXTURENAME3	_T("data/texture/game/gauge002.png")
#define GAUGE_TEXTURENAME4	_T("data/texture/game/gauge003.png")
#define GAUGE_TEXTURENAME5	_T("data/texture/game/gauge004.png")
#define GAUGE_TEXTURENAME6	_T("data/texture/game/gauge005.png")
#define GAUGE_TEXTURENAME7	_T("data/texture/game/gauge006.png")
#define GAUGE_TEXTURENAME8	_T("data/texture/game/gauge007.png")
#define GAUGE_TEXTURENAME9	_T("data/texture/game/gauge008.png")
#define GAUGE_TEXTURENAME10	_T("data/texture/game/gauge009.png")
#define GAUGE_TEXTURENAME11	_T("data/texture/game/gauge010.png")
#define GAUGETEXTNO		(12)
// サイズX
// サイズY

// 構造体定義
// プロトタイプ宣言
// グローバル変数
static ID3D11ShaderResourceView*	g_pTexture[GAUGETEXTNO];				// テクスチャ
static ID3D11ShaderResourceView*	g_pSTexture;				// テクスチャ

// 初期化処理
HRESULT InitGauge( void )
{
	HRESULT hr = S_OK;
	// テクスチャ読み込み
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME , &g_pTexture[0]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME1, &g_pTexture[1]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME2, &g_pTexture[2]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME3, &g_pTexture[3]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME4, &g_pTexture[4]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME5, &g_pTexture[5]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME6, &g_pTexture[6]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME7, &g_pTexture[7]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME8, &g_pTexture[8]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME9, &g_pTexture[9]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME10, &g_pTexture[10]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME11, &g_pTexture[11]);
	return hr;
}

HRESULT InitStartGauge(void)
{
	HRESULT hr = S_OK;
	// テクスチャ読み込み
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME10, &g_pSTexture);
	return hr;
}

void UninitGauge( void )
{
	// テクスチャ開放
	for (int i = 0; i < GAUGETEXTNO; i++)
	{
		SAFE_RELEASE(g_pTexture[i]);
	}
}

void UninitStartGauge(void)
{
	SAFE_RELEASE(g_pSTexture);
}

void UpdateGauge( void )
{
	// １フレームごとの更新処理
}

//pos:左端座標
//percent:100%→1.0として受け取る
void DrawGauge(XMFLOAT2 pos, float percent)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	SetPolygonTexture(g_pTexture[0]);
	SetPolygonSize(GAUGE_SIZE_X*percent, GAUGE_SIZE_Y);
	SetPolygonPos(pos.x + GAUGE_SIZE_X * percent / 2, pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(percent, 1.0f);

	DrawPolygon(pDeviceContext);

	SetPolygonFrameSize(1.0f, 1.0f);
}

void DrawGauge2(XMFLOAT2 pos, float percent)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	SetPolygonTexture(g_pTexture[0]);
	SetPolygonSize(415.0f*percent, 72.0f);
	SetPolygonPos(pos.x + 415.0f * percent / 2, pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(percent, 1.0f);

	DrawPolygon(pDeviceContext);

	SetPolygonFrameSize(1.0f, 1.0f);
}

void DrawGauge3(XMFLOAT2 pos, XMFLOAT2 size, float percent,int no)
{
	static float Pc;
	Pc = percent;
	if (Pc > 1.0f)Pc = 1.0f;
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	SetPolygonTexture(g_pTexture[no]);
	SetPolygonSize(size.x*Pc, size.y);
	SetPolygonPos(pos.x + size.x * Pc / 2, pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(Pc, 1.0f);
	DrawPolygon(pDeviceContext);
	SetPolygonFrameSize(1.0f, 1.0f);
}

void DrawGaugeLeft3(XMFLOAT2 pos, XMFLOAT2 size, float percent, int no)
{
	static float Pc;
	Pc = percent;
	if (Pc > 1.0f)Pc = 1.0f;
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	SetPolygonTexture(g_pTexture[no]);
	SetPolygonSize(size.x*Pc, size.y);
	SetPolygonPos(pos.x + size.x * Pc / 2 - size.x*Pc, pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(Pc, 1.0f);
	DrawPolygon(pDeviceContext);
	SetPolygonFrameSize(1.0f, 1.0f);
}

void DrawLoadGauge(float percent)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	SetPolygonTexture(g_pSTexture);
	SetPolygonSize(250.0f * percent, 10.0f);
	SetPolygonAngle(0.0f);
	SetPolygonPos(375.0f + 250.0f * percent / 2, -280.0f);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(percent, 1.0f);
	DrawPolygon(pDeviceContext);
	SetPolygonFrameSize(1.0f, 1.0f);
}
