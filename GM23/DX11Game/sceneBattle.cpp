#include "sceneBattle.h"
#include "text.h"
#include "gauge.h"
#include"input.h"
#include "Moji.h"
#include "Camera.h"
#include "billboard.h"

//==========================================================
//初期化
//==========================================================

_tDATA2 player[2];
Moji	text;
static wchar_t			g_battle[5][256] =
{ L"回避！" ,
L"プレイヤー１の攻撃" ,
L"プレイヤー２の攻撃" ,
L"プレイヤー１の勝ち！" ,
L"プレイヤー２の勝ち！" };
static int turn;
static int textNo[2];

HRESULT InitBattle()
{
	HRESULT hr = S_OK;
	HWND hWnd = GetMainWnd();
	hr = InitGauge();
	hr = InitText();
	hr = text.Init(GetSwapChain());
	hr = InitBillboard();
	GetCamera()->Init();
	player[0].Attack = 3000;
	player[0].Defense = 1000;
	player[0].EvasionRate = 500;
	player[0].Guts = 300;
	player[0].HP = 10000;
	player[0].INT = 600;
	player[0].Speed = 700;
	player[1].Attack = 3000;
	player[1].Defense = 1000;
	player[1].EvasionRate = 500;
	player[1].Guts = 300;
	player[1].HP = 10000;
	player[1].INT = 600;
	player[1].Speed = 700;
	turn = 0;
	textNo[0] = -1;
	textNo[1] = 0;
	return hr;
}

//==========================================================
//後片付け
//==========================================================

void UninitBattle()
{
	UninitGauge();
	UninitText();
	UninitBillboard();
}

//==========================================================
//更新
//==========================================================

void UpdateBattle()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		turn++;
		if (turn > 2)turn = 0;
		if (turn == 0)
		{
			if (rand() % 1000 > player[1].EvasionRate)
			{
				if (player[0].Attack > player[1].Defense)
				{
					player[1].HP -= player[0].Attack - player[1].Defense;
					textNo[1] = player[0].Attack - player[1].Defense;
				}
				else
				{
					player[1].HP -= 1;
					textNo[1] = 1;
				}
				textNo[0] = 1;
			}
			else textNo[0] = 0;

		}
		else
		{
			if (rand() % 1000 > player[0].EvasionRate)
			{
				if (player[1].Attack > player[0].Defense)
				{
					player[0].HP -= player[1].Attack - player[0].Defense;
					textNo[1] = player[1].Attack - player[0].Defense;
				}
				else
				{
					player[0].HP -= 1;
					textNo[1] = 1;
				}
				textNo[0] = 2;
			}
			else textNo[0] = 0;
		}
	}
	if (player[0].HP <= 0)textNo[0] = 4;
	if (player[1].HP <= 0)textNo[0] = 3;
	UpdateGauge();
	UpdateText();
	UpdateBillboard();
	GetCamera()->Update();
}

//==========================================================
//描画
//==========================================================
void DrawBattle()
{
	DrawBillboard();
}

void Draw2DBattle()
{
	Draw_CompleteNo(player[0].Attack, XMFLOAT2(130, 300), 0.5f);
	Draw_CompleteNo(player[0].Defense, XMFLOAT2(130, 250), 0.5f);
	Draw_CompleteNo(player[0].EvasionRate, XMFLOAT2(130, 200), 0.5f);
	Draw_CompleteNo(player[0].Guts, XMFLOAT2(130, 150), 0.5f);
	Draw_CompleteNo(player[0].HP, XMFLOAT2(130, 100), 0.5f);
	Draw_CompleteNo(player[0].INT, XMFLOAT2(130, 50), 0.5f);
	Draw_CompleteNo(player[0].Speed, XMFLOAT2(130, 0), 0.5f);
	DrawGauge3(XMFLOAT2(160, 300), XMFLOAT2(100, 30), (float)player[0].Attack / 9999.0f, 5);
	DrawGauge3(XMFLOAT2(160, 250), XMFLOAT2(100, 30), (float)player[0].Defense / 9999.0f, 5);
	DrawGauge3(XMFLOAT2(160, 200), XMFLOAT2(100, 30), (float)player[0].EvasionRate / 9999.0f, 5);
	DrawGauge3(XMFLOAT2(160, 150), XMFLOAT2(100, 30), (float)player[0].Guts / 9999.0f, 5);
	DrawGauge3(XMFLOAT2(160, 100), XMFLOAT2(100, 30), (float)player[0].HP / 9999.0f, 5);
	DrawGauge3(XMFLOAT2(160, 50), XMFLOAT2(100, 30), (float)player[0].INT / 9999.0f, 5);
	DrawGauge3(XMFLOAT2(160, 0), XMFLOAT2(100, 30), (float)player[0].Speed / 9999.0f, 5);
	Draw_CompleteNo(player[1].Attack, XMFLOAT2(-50, 300), 0.5f);
	Draw_CompleteNo(player[1].Defense, XMFLOAT2(-50, 250), 0.5f);
	Draw_CompleteNo(player[1].EvasionRate, XMFLOAT2(-50, 200), 0.5f);
	Draw_CompleteNo(player[1].Guts, XMFLOAT2(-50, 150), 0.5f);
	Draw_CompleteNo(player[1].HP, XMFLOAT2(-50, 100), 0.5f);
	Draw_CompleteNo(player[1].INT, XMFLOAT2(-50, 50), 0.5f);
	Draw_CompleteNo(player[1].Speed, XMFLOAT2(-50, 0), 0.5f);
	DrawGaugeLeft3(XMFLOAT2(-160, 300), XMFLOAT2(100, 30), (float)player[1].Attack / 9999.0f, 5);
	DrawGaugeLeft3(XMFLOAT2(-160, 250), XMFLOAT2(100, 30), (float)player[1].Defense / 9999.0f, 5);
	DrawGaugeLeft3(XMFLOAT2(-160, 200), XMFLOAT2(100, 30), (float)player[1].EvasionRate / 9999.0f, 5);
	DrawGaugeLeft3(XMFLOAT2(-160, 150), XMFLOAT2(100, 30), (float)player[1].Guts / 9999.0f, 5);
	DrawGaugeLeft3(XMFLOAT2(-160, 100), XMFLOAT2(100, 30), (float)player[1].HP / 9999.0f, 5);
	DrawGaugeLeft3(XMFLOAT2(-160, 50), XMFLOAT2(100, 30), (float)player[1].INT / 9999.0f, 5);
	DrawGaugeLeft3(XMFLOAT2(-160, 0), XMFLOAT2(100, 30), (float)player[1].Speed / 9999.0f, 5);
	if(textNo[0] != -1)text.Draw(g_battle[textNo[0]], lstrlen(g_battle[textNo[0]]), 640, 500/*座標1*/, 940, 600/*座標2*/);
}
