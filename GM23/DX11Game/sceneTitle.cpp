#include "sceneTitle.h"
#include "text.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "Moji.h"
#include "HS_effect.h"
#include "Camera.h"
#include "model.h"
#include "fade.h"
#include "D2DText.h"
#include "D2DDrawMng.h"
#include "TitleText.h"

#define EXPLOSION_TEXTURENAME4		"data/texture/HS/click2.png"		// ポリゴンに表示させる画像
#define MESSAGENO	(5)

static GameEffect		effect;
static bool		StartSwitch;
static int		MenuNo, MenuSwitch, AnimeNo,TextNo[2],BattleNo;
static time_t	NowTime, AltTime,TextTime[2];
static Moji		g_Moji;
static float	Scroll;
wchar_t			g_AAA[MESSAGENO][256] = 
{ L"こんにちわ、私の名前はIAです。これからよろしくお願いします。" , 
L"いつまでさぼっているんですか？\n早く次の育成をしてください。" ,  
L"ぶつからなきゃ伝わらないことだってあるよ。\n例えば、自分がどれだけ真剣なのか、とかね" ,  
L"こんにちわ" ,  
L"皆さんこんにちわ" , };


using namespace F_lib_Render;
D2DTextParams* g_Texts;


HRESULT InitTitle()
{
	HRESULT hr = S_OK;
	HWND hWnd = GetMainWnd();
	hr = InitText();
	hr = InitTitleText();
	hr = InitModel();
	GetCamera()->Init();
	effect.HS_InitExplosion((char*)EXPLOSION_TEXTURENAME4, XMFLOAT2(125,125), XMFLOAT2(5, 4),1);
	StartSwitch = true;
	MenuNo = 1;
	AnimeNo = 0;
	MenuSwitch = 0;
	BattleNo = 0;
	Scroll = 0;
	TextNo[0] = 0;//文字数
	TextNo[1] = -1;//表示メッセージ
	TextTime[0] = TextTime[1] = timeGetTime();
	hr = g_Moji.Init(GetSwapChain());
	if (FAILED(hr)) { return hr; }
	PlaySound(SOUND_LABEL_BGM003);

	TextData td;
	td.Str = "コントローラ";
	//td.Form = TextData::FORM::Rect;
	td.Data->Color = D2D1::ColorF(D2D1::ColorF::Red);
	td.Data->font = Font::Impact;
	td.Data->fontSize = 50;
	
	g_Texts = new D2DTextParams();
	g_Texts->SetData(&td);
	g_Texts->SetDrawFlag(false);
	return hr;
}

//==========================================================
//後片付け
//==========================================================

void UninitTitle()
{
	UninitText();
	UninitTitleText();
	UninitModel();
	SAFE_DELETE(g_Texts);
	GetTextMng()->RemoveAll();
	effect.HS_UninitExplosion();
}

//==========================================================
//更新
//==========================================================

void UpdateTitle()
{
	UpdateText();
	UpdateTitleText();
	UpdateModel();
	GetCamera()->Update();
	effect.HS_UpdateExplosion();
	int No;
	No = HS_TitleMouseCollision(0) + 1;
	TextTime[0] = NowTime = timeGetTime();
	if (No != 0 && No < 6 && GetMouseTrigger(MOUSEBUTTON_L))
	{
		effect.HS_SetExplosion(XMFLOAT3((float)GetWindowMousePosX(), (float)GetWindowMousePosY(), 0),true);
		PlaySound(SOUND_LABEL_SE_05);
		if (MenuNo != No)
		{
			if (GetRotationSwitch())MenuNo = No;
			RotationSwitchOn();
		}
	}
	else if (No == 8 && GetMouseTrigger(MOUSEBUTTON_L))
	{
		effect.HS_SetExplosion(XMFLOAT3((float)GetWindowMousePosX(), (float)GetWindowMousePosY(), 0), true);
		PlaySound(SOUND_LABEL_SE_05);
		if(!StartSwitch)StartSwitch = !StartSwitch;		
	}
	else if (No == 7 && GetMouseTrigger(MOUSEBUTTON_L))
	{
		if (GetMenuPos() >= 0.0f)MenuSwitch = 1;
		if (GetMenuPos() <= -190.0f)MenuSwitch = 2;
	}
	else if(No == 0 && GetMouseTrigger(MOUSEBUTTON_L))
	{
		effect.HS_SetExplosion(XMFLOAT3((float)GetWindowMousePosX(), (float)GetWindowMousePosY(), 0), true);
		PlaySound(SOUND_LABEL_SE_05);
		if ((int)GetWindowMousePosX() < -100 && (int)GetWindowMousePosX() > -300
			&& (int)GetWindowMousePosY() < 180 && (int)GetWindowMousePosY() > -180)
		{
			/*if (AnimeNo == 0)AnimeSwitch(0,6);
			NowTime = timeGetTime();
			AltTime = NowTime;
			AnimeNo = 6;*/
			if(TextNo[1] == -1)TextNo[1] = rand() % MESSAGENO;
			else if (TextNo[0] == lstrlen(g_AAA[TextNo[1]]))
			{
				TextNo[0] = 0;
				TextNo[1] = -1;
			}
			else TextNo[0] = lstrlen(g_AAA[TextNo[1]]);
		}
	}
	switch (MenuNo)
	{
	case 1:
		break;
	case 2:
		switch (BattleNo)
		{
		case 0:
			if (No == 9 && GetMouseTrigger(MOUSEBUTTON_L))
			{
				BattleNo = 1;
			}
			else if (No == 10 && GetMouseTrigger(MOUSEBUTTON_L))
			{
				BattleNo = 2;
			}
			else if (No == 11 && GetMouseTrigger(MOUSEBUTTON_L))
			{
				BattleNo = 3;
			}
			break;
		case 1:
			//if(GetKeyTrigger(VK_SHIFT))Scroll
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if (abs(TextTime[0] - TextTime[1]) > 100)
	{
		if (TextNo[1] != -1 && TextNo[0] < lstrlen(g_AAA[TextNo[1]]))TextNo[0]++;
		TextTime[1]= TextTime[0];
	}
	/*if (abs(NowTime - AltTime) > 5600)
	{
		AnimeSwitch(6, 0);
		AnimeNo = 0;
	}*/
	if (GetKeyTrigger(VK_SPACE) && StartSwitch)StartSwitch = !StartSwitch;
	if (GetKeyTrigger(VK_RETURN))
	{
		switch (MenuNo)
		{
		case(1):
			StartFade(SCENE_TITLE, 30);
			break;
		case(2):
			StartFade(SCENE_TITLE, 30);
			break;
		case(3):
			StartFade(SCENE_GAME, 30);
			break;
		case(4):
			StartFade(SCENE_CLEAR, 30);
			break;
		case(5):
			StartFade(SCENE_TITLE, 30);
			break;
		default:
			break;
		}
	}
	if (MenuSwitch == 1)MenuPosAdo(-10.0f);
	if (MenuSwitch == 2)MenuPosAdo(10.0f);
}

//==========================================================
//描画
//==========================================================

void DrawTitle()
{
	if (StartSwitch)
	{

	}
	else
	{
		GetLight()->SetDisable();
		DrawModel();
	}
}

void Draw2DTitle()
{
	if (StartSwitch)
	{

	}
	else
	{
		switch (MenuNo)
		{
		case 1:
			break;
		case 2:
			switch (BattleNo)
			{
			case 0:
				for (int i = 8; i < 11; i++)
				{
					if (!GetRotationSwitch())continue;
					Draw_Text(i);
				}
				DrawTitleText(MenuNo);
				break;
			case 1:
				DrawTitleText(0);
				break;
			case 2:
				DrawTitleText(0);
				break;
			case 3:
				DrawTitleText(0);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		for (int i = 5; i < 8; i++)
		{
			Draw_Text(i);
		}
		for (int i = 0; i < 5; i++)
		{
			Draw_Text(i);
		}
		effect.HS_DrawExplosion();
		if(TextNo[1] > -1)g_Moji.Draw(g_AAA[TextNo[1]], TextNo[0], 100, 400/*座標1*/, 700, 600/*座標2*/);
	}
}

int GetMenuNo()
{
	return MenuNo;
}

int GetMenuSwitch()
{
	return MenuSwitch;
}

void SetMenuSwitch(int no)
{
	MenuSwitch = no;
}