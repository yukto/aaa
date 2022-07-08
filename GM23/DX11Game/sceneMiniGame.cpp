#include "sceneMiniGame.h"
#include "sceneGame.h"
#include "MiniGametext.h"
#include "input.h"
#include "HS_Gametext1.h"
#include "text.h"

static XMFLOAT2	Sc,ScVel;
static int count, AdStatus;
//==========================================================
//‰Šú‰»
//==========================================================
HRESULT InitMiniGame()
{
	//‰Šú‰»
	HRESULT hr = S_OK;
	HWND hWnd = GetMainWnd();
	InitMiniGameText(0);
	Sc = XMFLOAT2(0.0f, 0.0f);
	ScVel = XMFLOAT2(0.02f, 0.02f);
	count = 2000;
	AdStatus = 0;
	return hr;
}

//==========================================================
//Œã•Ð•t‚¯
//==========================================================
int UninitMiniGame()
{
	UninitMiniGameText();
	return AdStatus = GetMiniGamePLAYER();
}

//==========================================================
//XV
//==========================================================
void UpdateMiniGame()
{
	if (Sc.x >= 1.0f)
	{
		count--;
		UpdateMiniGameText();
	}
	if(count == 0 && Sc.x >= 1.0f)
	{
		Sc = XMFLOAT2(0.98f, 0.98f);
		ScVel = XMFLOAT2(-0.02f, -0.02f);
	}
	if (Sc.x < 1.0f)
	{
		Sc.x += ScVel.x;
		Sc.y += ScVel.y;
	}
	if (Sc.x < 0.0f)
	{
		Sc = XMFLOAT2(0.0f, 0.0f);
		ScVel = XMFLOAT2(0.0f, 0.0f);
		UninitGameMiniGame();
	}
}

//==========================================================
//•`‰æ
//==========================================================

void DrawMiniGame()
{

}

void Draw2DMiniGame()
{
	for (int i = 0; i < 15; i++)
	{
		Draw_MiniGameTextAll(i, Sc);
		if(i > 2 && abs((LONG)GetMiniGameTextPos(i).x) < SCREEN_CENTER_X)Draw_HS_Gametext1All(GetMiniGameTextMNo(i) - 55, XMFLOAT2((GetMiniGameTextPos(i).x + 10.0f) * Sc.x, GetMiniGameTextPos(i).y * Sc.y), XMFLOAT2(50 * Sc.x, 50 * Sc.y));
	}
	if (Sc.x >= 1.0f)Draw_CompleteNo(GetMiniGamePLAYER(), XMFLOAT2(600, 300), 1.0f);
	DrwaEffectText();
}
