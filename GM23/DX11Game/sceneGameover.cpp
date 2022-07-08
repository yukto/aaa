#include "sceneGameover.h"
//=============================================================================
//
// �^�C�g���V�[�� [sceneGameover.cpp]
// Author : SHOUEI HIRAMATSU 
//
//=============================================================================

#include "sceneGameover.h"
#include "Bullet.h"
#include "main.h"
#include"input.h"
#include"end.h"

//==========================================================
//������
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
		MessageBox(hWnd, _T("�����j���O�}������"), WINDOW_NAME, MB_OK | MB_ICONSTOP);
		return hr;
	}
	endcount = 0;
	return hr;
}

//==========================================================
//��Еt��
//==========================================================


void UninitGameover()
{
	UninitBg();
	UninitEnd();
}

//==========================================================
//�X�V
//==========================================================


void UpdateGameover()
{
	if (GetKeyTrigger(VK_RETURN)|| endcount>1400)StartSceneChange(SCENE_BREAK);
	UpdateBg();
	UpdateEnd();
	endcount++;
}

//==========================================================
//�`��
//==========================================================

void DrawGameover()
{
	DrawBg();
	DrawEnd();
}
