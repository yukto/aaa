#include "C_Text.h"
#include "Texture.h"
#include "polygon.h"

HRESULT CText::InitCText(char * text, XMFLOAT2 size, XMFLOAT3 pos)
{
	HRESULT hr = S_OK;

	// テクスチャ読み込み
	ID3D11Device*	pDevice = GetDevice();
	hr = CreateTextureFromFile(pDevice, text, &g_text.pTexture);

	//パラメータの初期化
	g_text.Position = pos;
	g_text.Size = size;
	g_text.Angle = 0.0f;
	g_text.vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_text.Scale = XMFLOAT2(1.0f, 1.0f);
	g_text.TexCoord = XMFLOAT2(1.0f, 1.0f);
	g_text.TexFrameSize = XMFLOAT2(1.0f, 1.0f);
	g_text.Alfa = 1.0f;
	g_text.AlfaAd = 0.0f;
	g_text.AngleAd = 0.0f;
	g_text.State = 1;
	return hr;
}

void CText::UninitCText()
{
	SAFE_RELEASE(g_text.pTexture);
}

void CText::UpdateCText()
{
	g_text.Position.x += g_text.vel.x;
	g_text.Position.y += g_text.vel.y;
	g_text.Angle += g_text.AngleAd;
	g_text.Alfa += g_text.AlfaAd;
	if (g_text.Alfa >= 1.0f)g_text.Alfa = 1.0f;
	if (g_text.Alfa <= 0.0f)g_text.Alfa = 0.0f;
	if (g_text.Alfa >= 1.0f || g_text.Alfa <= 0.0f)g_text.AlfaAd = -g_text.AlfaAd;
}

void CText::DrawCText()
{
	SetPolygonAlpha(g_text.Alfa);
	//ポリゴンの情報設定
	SetPolygonPos(g_text.Position.x, g_text.Position.y);
	SetPolygonSize(g_text.Size.x, g_text.Size.y);
	SetPolygonAngle(g_text.Angle);
	//degree(デグリー)値
	SetPolygonUV(g_text.TexCoord.x, g_text.TexCoord.y);		  //左上のUV座標
	SetPolygonFrameSize(g_text.TexFrameSize.x, g_text.TexFrameSize.y);  //横幅縦幅
	SetPolygonTexture(g_text.pTexture);	  //テクスチャ指定

	// ポリゴンの描画処理
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	SetPolygonAlpha(1.0f);
}