#include "sceneGameover.h"
//=============================================================================
//
// タイトルシーン [sceneGameover.cpp]
// Author : SHOUEI HIRAMATSU 
//
//=============================================================================

#include "sceneGameover.h"
#include "Bullet.h"
#include "main.h"
#include"input.h"
#include"end.h"

//==========================================================
//初期化
//==========================================================
static int endcount;

HRESULT InitGameover()
{
	HRESULT hr = S_OK;
	HWND hWnd = GetMainWnd();
	hr = InitBg();
	hr = InitEnd();
	if (FAILED(hr))
	{
		MessageBox(hWnd, _T("ランニングマン初期"), WINDOW_NAME, MB_OK | MB_ICONSTOP);
		return hr;
	}
	endcount = 0;
	return hr;
}

//==========================================================
//後片付け
//==========================================================


void UninitGameover()
{
	UninitBg();
	UninitEnd();
}

//==========================================================
//更新
//==========================================================


void UpdateGameover()
{
	if (GetKeyTrigger(VK_RETURN)|| endcount>1400)StartSceneChange(SCENE_BREAK);
	UpdateBg();
	UpdateEnd();
	endcount++;
}

//==========================================================
//描画
//==========================================================

void DrawGameover()
{
	DrawBg();
	DrawEnd();
}
