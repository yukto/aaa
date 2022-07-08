//=============================================================================
//
// フェード処理 [fade.cpp]
//
//=============================================================================
#include "fade.h"
#include"Texture.h"
#include "polygon.h"

// マクロ定義
#define FADE_POS_X		(0)		// 表示位置X
#define FADE_POS_Y		(0)		// 表示位置Y
#define FADE_SIZE_X		(SCREEN_WIDTH)	// サイズX
#define FADE_SIZE_Y		(SCREEN_HEIGHT)	// サイズY

#define FADE_RED		(0.0f)
#define FADE_GREEN		(0.0f)
#define FADE_BLUE		(0.0f)

#define TEXTNAME1	_T("data/texture/HS/素卵.png")
#define TEXTNAME2	_T("data/texture/HS/素卵2.png")
#define TEXTNAME3	_T("data/texture/HS/素卵3.png")
#define TEXTNAME4	_T("data/texture/HS/素卵4.png")
#define TEXTNAME5	_T("data/texture/HS/素卵5.png")
#define TEXTNAME6	_T("data/texture/HS/素卵6.png")
#define TEXTNAME6	_T("data/texture/HS/素卵6.png")
#define TEXTNAME7	_T("data/texture/clear01.png")
#define TEXT_NO		(300)
// 構造体定義
typedef struct {
	XMFLOAT3		g_Position;		//座標
	XMFLOAT2		g_Size;			//サイズ
	float			g_Angle;		//回転角度
	XMFLOAT3		g_vel;
	XMFLOAT2		g_Scale;
	XMFLOAT2		g_TexCoord;		//テクスチャ座標(ポリゴンの左上)
	XMFLOAT2		g_TexFrameSize; //テクスチャを張り付けるサイズ
	float			Alfa;
	float			AlfaAd;
	float			AngleAd;
	bool			nState;
} FADE_2D;
// プロトタイプ宣言
// グローバル変数
static float			g_fAlpha = 1.0f;	// 透明度
static E_FADE			g_nFade = E_FADE_IN;	// フェードの状態
static E_TYPE_SCENE		g_stateNext = SCENE_TITLE;	// フェード後の状態
static int				g_nFrame = 30;	// フェードフレーム数
static FADE_2D			textno[TEXT_NO];
static ID3D11ShaderResourceView*	g_pTexture[7];

// 初期化処理
HRESULT InitFade( void )
{
	g_fAlpha = 0.0f;			// 最初はフェードインから
	g_nFade = E_FADE_NONE;
	g_stateNext = SCENE_TITLE;
	g_nFrame = 30;

	ID3D11Device* pDevice = GetDevice();

	//テクスチャ
	CreateTextureFromFile(pDevice, TEXTNAME1, &g_pTexture[0]);
	CreateTextureFromFile(pDevice, TEXTNAME2, &g_pTexture[1]);
	CreateTextureFromFile(pDevice, TEXTNAME3, &g_pTexture[2]);
	CreateTextureFromFile(pDevice, TEXTNAME4, &g_pTexture[3]);
	CreateTextureFromFile(pDevice, TEXTNAME5, &g_pTexture[4]);
	CreateTextureFromFile(pDevice, TEXTNAME6, &g_pTexture[5]);
	CreateTextureFromFile(pDevice, TEXTNAME7, &g_pTexture[6]);
	for (int i = 0; i < TEXT_NO; i++)
	{
		textno[i].g_Position = XMFLOAT3(SCREEN_CENTER_X + 200.0f + (float)(rand() % 1400),0.0f + (float)(rand() % 760 - 380), 0.0f);
		textno[i].g_Size = XMFLOAT2(200, 200);
		textno[i].g_Angle = 0.0f;
		textno[i].g_vel = XMFLOAT3(-10.0f - (float)(rand() % 6), 0.0f, 0.0f);
		textno[i].g_Scale = XMFLOAT2(1.0f, 1.0f);
		textno[i].g_TexCoord = XMFLOAT2(1.0f, 1.0f);
		textno[i].g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
		textno[i].Alfa = 1.0f;
		textno[i].AlfaAd = 0.0f;
		textno[i].AngleAd = (float)(rand() % 4 + 1);
		textno[i].nState = false;
	}
	textno[TEXT_NO - 1].g_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	textno[TEXT_NO - 1].g_Size = XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
	textno[TEXT_NO - 1].g_vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	textno[TEXT_NO - 1].AngleAd = 0.0f;
	return S_OK;
}

void UninitFade( void )
{
}

void UpdateFade( void )
{
	for (int i = 0; i < TEXT_NO -1; i++)
	{
		if (!textno[i].nState)continue;
		textno[i].g_Angle += textno[i].AngleAd;
		textno[i].g_Position.x += textno[i].g_vel.x;
	}
	for (int i = 0; i < TEXT_NO - 1; i++)
	{
		if (textno[i].g_Position.x > SCREEN_CENTER_X + 400)break;
		if(i == TEXT_NO - 2 && g_nFade == E_FADE_OUT && g_fAlpha < 1.0f)g_fAlpha += 0.03f;
		else if (i == TEXT_NO - 2 && g_nFade == E_FADE_IN)g_fAlpha -= 0.03f;
	}
	for (int i = 0; i < TEXT_NO - 1; i++)
	{
		if (textno[i].g_Position.x > -SCREEN_CENTER_X - 150)break;
		if (i == TEXT_NO - 2 && g_nFade == E_FADE_OUT)g_fAlpha = 1.1f;
		else if (i == TEXT_NO - 2 && g_nFade == E_FADE_IN)g_fAlpha = -0.1f;
	}
	// １フレームごとの更新処理
	switch( g_nFade )
	{
	case E_FADE_OUT:	// フェードアウト
		if (g_fAlpha == 1.1f)
		{	// フェードアウトが終わったのでフェードインに変更
			g_fAlpha = 1.0f;
			g_nFade  = E_FADE_LOAD;
			for (int i = 0; i < TEXT_NO - 1; i++)
			{
				textno[i].g_Position = XMFLOAT3(SCREEN_CENTER_X + 200.0f + (float)(rand() % 1400), 0.0f + (float)(rand() % 760 - 380), 0.0f);
				textno[i].nState = false;
			}
		}
		break;
	case E_FADE_LOAD:
		StartSceneChange(g_stateNext);
		g_nFade = E_FADE_IN;
		for (int i = 0; i < TEXT_NO - 1; i++)
		{
			textno[i].nState = true;
		}
		break;
	case E_FADE_IN:	// フェードイン
		if (g_fAlpha == -0.1f)
		{
				// フェードインが終わった
			g_fAlpha = 0.0f;
			g_nFade = E_FADE_NONE;
			for (int i = 0; i < TEXT_NO - 1; i++)
			{
				textno[i].g_Position = XMFLOAT3(SCREEN_CENTER_X + 200.0f + (float)(rand() % 1400), 0.0f + (float)(rand() % 760 - 380), 0.0f);
				textno[i].nState = false;
			}
		}
		break;
	}

}

void DrawFade( void )
{
	if(g_nFade == E_FADE_NONE)return;
	SetPolygonAlpha(g_fAlpha);
	//ポリゴンの情報設定
	SetPolygonPos(textno[TEXT_NO - 1].g_Position.x, textno[TEXT_NO - 1].g_Position.y);
	SetPolygonSize(textno[TEXT_NO - 1].g_Size.x, textno[TEXT_NO - 1].g_Size.y);
	SetPolygonAngle(textno[TEXT_NO - 1].g_Angle);
	//degree(デグリー)値
	SetPolygonUV(textno[TEXT_NO - 1].g_TexCoord.x, textno[TEXT_NO - 1].g_TexCoord.y);		  //左上のUV座標
	SetPolygonFrameSize(textno[TEXT_NO - 1].g_TexFrameSize.x, textno[TEXT_NO - 1].g_TexFrameSize.y);  //横幅縦幅
	SetPolygonTexture(g_pTexture[6]);	  //テクスチャ指定

	// ポリゴンの描画処理
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
	for (int i = 0; i < TEXT_NO - 1; i++)
	{
		SetPolygonAlpha(textno[i].Alfa);
		//ポリゴンの情報設定
		SetPolygonPos(textno[i].g_Position.x, textno[i].g_Position.y);
		SetPolygonSize(textno[i].g_Size.x, textno[i].g_Size.y);
		SetPolygonAngle(textno[i].g_Angle);
		//degree(デグリー)値
		SetPolygonUV(textno[i].g_TexCoord.x, textno[i].g_TexCoord.y);		  //左上のUV座標
		SetPolygonFrameSize(textno[i].g_TexFrameSize.x, textno[i].g_TexFrameSize.y);  //横幅縦幅
		SetPolygonTexture(g_pTexture[i % 6]);	  //テクスチャ指定

		// ポリゴンの描画処理
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
		DrawPolygon(pDeviceContext);
	}
	SetPolygonAlpha(1.0f);
	SetPolygonAngle(0.0f);
	SetPolygonColor(1.0f, 1.0f, 1.0f);
}

// フェード開始
// stateNext:
// nFrame:
void StartFade( E_TYPE_SCENE stateNext, int nFrame/* = 30 */)
{
	if (GetFade() != E_FADE_NONE) return;
	g_nFade = E_FADE_OUT;
	g_stateNext = stateNext;
	if (nFrame <= 0) nFrame = 1;
	g_nFrame = nFrame;
	for (int i = 0; i < TEXT_NO - 1; i++)
	{
		textno[i].nState = true;
	}
}

// 現在フェード中ですか？
E_FADE GetFade()
{
	return g_nFade;
}

float GetFadeAlpha()
{
	return g_fAlpha;
}