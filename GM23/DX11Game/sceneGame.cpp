#include "sceneGame.h"
#include "sceneMiniGame.h"
#include "HS_Gametext1.h"
#include "input.h"
#include "text.h"
#include "HS_data.h"
#include "gauge.h"
#include "collision.h"
#include "fade.h"
#include "HS_effect.h"
#include "Camera.h"

static bool MinigameSwitch,MakeSwitch,InputSwitch;
static int count,turn,codeNo,code[10],UpStNo;
static _tDATA MakeMonster;

//==========================================================
//‰Šú‰»
//==========================================================
HRESULT InitGame()
{
	//‰Šú‰»
	HRESULT hr = S_OK;
	HWND hWnd = GetMainWnd();
	hr = InitHS_Gametext1();
	hr = InitText();
	hr = InitGauge();
	GetCamera()->Init();
	MinigameSwitch = false;
	MakeSwitch = true;
	InputSwitch = true;
	count = 0;
	turn = 0;
	codeNo = 0;
	UpStNo = 0;
	for (int i = 0; i < 10; i++)
	{
		code[i] = -1;
	}
	MakeMonster.Attack = 0;
	MakeMonster.Defense = 0;
	MakeMonster.EvasionRate = 0;
	MakeMonster.Guts = 0;
	MakeMonster.HP = 0;
	MakeMonster.INT = 0;
	MakeMonster.Speed = 0;
	return hr;
}

//==========================================================
//Œã•Ð•t‚¯
//==========================================================
void UninitGame()
{
	UninitHS_Gametext1();
	UninitText();
	UninitGauge();
}

//==========================================================
//XV
//==========================================================
void UpdateGame()
{
	if (MakeSwitch)
	{
		static int Kno;
		Kno = GetTrigerKeyNo();
		if ((Kno >= 65 && Kno <= 90) || (Kno >= 48 && Kno <= 57))
		{
			if (codeNo < 10 && InputSwitch)
			{
				if (Kno > 60)code[codeNo] = Kno - 55;//a-z
				else code[codeNo] = Kno - 48;//1-9
				codeNo++;
			}
		}
		if (GetKeyTrigger(VK_BACK) && codeNo > 0)
		{
			codeNo--;
			code[codeNo] = -1;
		}
		UpdateHS_Gametext1();
		UpdateText();
		UpdateGauge();
		if (TextCollision(XMFLOAT2(GetGAMETEXT_2Ddata(2).g_Position.x, GetGAMETEXT_2Ddata(2).g_Position.y),
			GetGAMETEXT_2Ddata(2).g_Size,0) && GetMouseTrigger(MOUSEBUTTON_L))
		{
			MakeSwitch = false;
			for (int i = 0; i < 10; i++)
			{
				if (code[i] == -1)break;
				MakeMonster.Attack += code[i] * 5;
				MakeMonster.Defense += code[i] * 4;
				MakeMonster.EvasionRate += code[i] * 2;
				MakeMonster.Guts += code[i] * 3;
				MakeMonster.HP += code[i] * 10;
				MakeMonster.INT += code[i];
				MakeMonster.Speed += code[i] * 6;
			}
		}
	}
	else
	{
		if (MinigameSwitch)
		{
			UpdateMiniGame();
		}
		else
		{

		}
	}
	if (GetKeyTrigger(VK_6))
	{
		UpStNo = 0;
		InitGameMiniGame();
	}
	if (GetKeyTrigger(VK_7))
	{
		UpStNo = 0;
		InitGameMiniGame();
	}
	if (GetKeyTrigger(VK_8))
	{
		UpStNo = 0;
		InitGameMiniGame();
	}
	if (GetKeyTrigger(VK_9))
	{
		UpStNo = 0;
		InitGameMiniGame();
	}
	if (GetKeyTrigger(VK_0))
	{
		UpStNo = 0;
		InitGameMiniGame();
	}

	if (TextCollision(XMFLOAT2(GetGAMETEXT_2Ddata(1).g_Position.x, GetGAMETEXT_2Ddata(1).g_Position.y),
		GetGAMETEXT_2Ddata(1).g_Size, 0) && GetMouseTrigger(MOUSEBUTTON_L))StartFade(SCENE_TITLE, 60);
	GetCamera()->Update();
}

//==========================================================
//•`‰æ
//==========================================================

void DrawGame()
{
	if (MakeSwitch)
	{
		
	}
	else
	{
		if (MinigameSwitch)
		{
			DrawMiniGame();

		}
		else
		{

		}
	}
}

void Draw2DGame()
{
	if (MakeSwitch)
	{
		for (int i = 0; i < 7; i++)
		{
			Draw_HS_Gametext2(i);
		}
		for (int i = 0; i < codeNo; i++)
		{
			if (code[i] == -1)break;
			Draw_HS_Gametext1All(code[i], XMFLOAT2((float)(160 + 30 * i),0.0f), XMFLOAT2(30, 30));
		}
		Draw_CompleteNo(MakeMonster.Attack, XMFLOAT2(-550, 200), 0.5f);
		Draw_CompleteNo(MakeMonster.Defense, XMFLOAT2(-550, 150), 0.5f);
		Draw_CompleteNo(MakeMonster.EvasionRate, XMFLOAT2(-550, 100), 0.5f);
		Draw_CompleteNo(MakeMonster.Guts, XMFLOAT2(-550, 50), 0.5f);
		Draw_CompleteNo(MakeMonster.HP, XMFLOAT2(-550, 0), 0.5f);
		Draw_CompleteNo(MakeMonster.INT, XMFLOAT2(-550, -50), 0.5f);
		Draw_CompleteNo(MakeMonster.Speed, XMFLOAT2(-550, -100), 0.5f);
		DrawGauge3(XMFLOAT2(-500, 200), XMFLOAT2(100, 30), (float)MakeMonster.Attack / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, 150), XMFLOAT2(100, 30), (float)MakeMonster.Defense / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, 100), XMFLOAT2(100, 30), (float)MakeMonster.EvasionRate / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, 50), XMFLOAT2(100, 30), (float)MakeMonster.Guts / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, 0), XMFLOAT2(100, 30), (float)MakeMonster.HP / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, -50), XMFLOAT2(100, 30), (float)MakeMonster.INT / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, -100), XMFLOAT2(100, 30), (float)MakeMonster.Speed / 9999.0f, 5);
	}
	else
	{
		Draw_CompleteNo(MakeMonster.Attack, XMFLOAT2(-550, 200), 0.5f);
		Draw_CompleteNo(MakeMonster.Defense, XMFLOAT2(-550, 150), 0.5f);
		Draw_CompleteNo(MakeMonster.EvasionRate, XMFLOAT2(-550, 100), 0.5f);
		Draw_CompleteNo(MakeMonster.Guts, XMFLOAT2(-550, 50), 0.5f);
		Draw_CompleteNo(MakeMonster.HP, XMFLOAT2(-550, 0), 0.5f);
		Draw_CompleteNo(MakeMonster.INT, XMFLOAT2(-550, -50), 0.5f);
		Draw_CompleteNo(MakeMonster.Speed, XMFLOAT2(-550, -100), 0.5f);
		DrawGauge3(XMFLOAT2(-500, 200), XMFLOAT2(100, 30), (float)MakeMonster.Attack / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, 150), XMFLOAT2(100, 30), (float)MakeMonster.Defense / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, 100), XMFLOAT2(100, 30), (float)MakeMonster.EvasionRate / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, 50), XMFLOAT2(100, 30), (float)MakeMonster.Guts / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, 0), XMFLOAT2(100, 30), (float)MakeMonster.HP / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, -50), XMFLOAT2(100, 30), (float)MakeMonster.INT / 9999.0f, 5);
		DrawGauge3(XMFLOAT2(-500, -100), XMFLOAT2(100, 30), (float)MakeMonster.Speed / 9999.0f, 5);
		if (MinigameSwitch)
		{
			Draw2DMiniGame();
		}
		else
		{

		}
	}
}

void InitGameMiniGame()
{
	MinigameSwitch = true;
	InitMiniGame();
}

void UninitGameMiniGame()
{
	MinigameSwitch = false;
	switch (UpStNo)
	{
	case 0:
		MakeMonster.Attack += (int)UninitMiniGame();
		break;
	case 1:
		MakeMonster.Defense += (int)UninitMiniGame();
		break;
	case 2:
		MakeMonster.HP += (int)UninitMiniGame();
		break;
	case 3:
		MakeMonster.INT += (int)UninitMiniGame();
		break;
	case 4:
		MakeMonster.Speed += (int)UninitMiniGame();
		break;
	default:
		UninitMiniGame();
		break;
	}
}

int GetUpStNo()
{
	return UpStNo;
}
