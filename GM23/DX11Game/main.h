//=============================================================================
//
// メイン処理 [main.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <mmsystem.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "resource.h"
#include "D2DDrawMng.h"
#include "D2DText.h"

#pragma warning(disable:4996)

// 本来はヘッダに書かない方が良い
using namespace DirectX;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){(x)->Release();x=nullptr;}}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if(x){delete(x);x=nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) {if(x){delete[](x);x=nullptr;}}
#endif

#define SCREEN_WIDTH	(1280)				// ウインドウの幅
#define SCREEN_HEIGHT	(720)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH/2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT/2)	// ウインドウの中心Ｙ座標

#define	NUM_VERTEX		(4)					// 頂点数
#define	NUM_POLYGON		(2)					// ポリゴン数

#define SinDeg(degree)	(sinf(XMConvertToRadians(degree)))
#define CosDeg(degree)	(cosf(XMConvertToRadians(degree)))

//列挙体定義
enum E_TYPE_SCENE
{
	SCENE_TITLE = 0,	//タイトル画面
	SCENE_GAME,
	SCENE_CLEAR,
	SCENE_CONFIG,
	SCENE_MENU,
	SCENE_BATTLE,

	MAX_SCENE			//←これは必ず一番最後
};

enum EBlendState {
	BS_NONE = 0,							// 半透明合成無し
	BS_ALPHABLEND,							// 半透明合成
	BS_ADDITIVE,							// 加算合成
	BS_SUBTRACTION,							// 減算合成

	MAX_BLENDSTATE
};

enum ECullMode {
	CULLMODE_NONE = 0,						// カリングしない
	CULLMODE_CW,							// 前面カリング
	CULLMODE_CCW,							// 背面カリング

	MAX_CULLMODE
};

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
typedef struct {
	XMFLOAT3 vtx;		// 頂点座標
	XMFLOAT4 diffuse;	// 拡散反射光
	XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_2D;

// 頂点フォーマット( 頂点座標[3D] / 法線ベクトル / 反射光 / テクスチャ座標 )
typedef struct {
	XMFLOAT3 vtx;		// 頂点座標
	XMFLOAT3 nor;		// 法線ベクトル
	XMFLOAT4 diffuse;	// 拡散反射光
	XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_3D;

typedef struct {
	int nPatNo;    //表示パターン番号
	int nCount;    //表示フレーム数
}ANIM_PAT;

class SCENE
{
public:
	HRESULT SInit();
	void SUninit();
	void SUpdate();
	void SDarw();
	void SDraw2D();
private:

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// 前方宣言
namespace F_lib_Render
{
	class D2DText;
	class D2DTextMng;
}

HWND GetMainWnd();
HINSTANCE GetInstance();
ID3D11Device* GetDevice();
IDXGISwapChain* GetSwapChain();
ID3D11DeviceContext* GetDeviceContext();
void SetZBuffer(bool bEnable);
void SetZWrite(bool bEnable);
void SetBlendState(int nBlendState);
void SetCullMode(int nCullMode);
void StartSceneChange(E_TYPE_SCENE next);
E_TYPE_SCENE GetCurrentScene();
int gettestnono();
F_lib_Render::D2DText*		GetD2DText();
F_lib_Render::D2DTextMng*	GetTextMng();
