//=============================================================================
//
// 入力処理 [input.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
static HRESULT InitKeyboard();
static void UninitKeyboard();
static HRESULT UpdateKeyboard();

static HRESULT InitJoystick();
static void UninitJoystick();
static HRESULT UpdateJoystick();

static HRESULT InitMouse();
static void UninitMouse();
static HRESULT UpdateMouse();

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static WORD				g_wKeyState[NUM_KEY_MAX];			// キーボードの押下状態を保持するワーク
static WORD				g_wKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガ状態を保持するワーク
static WORD				g_wKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース状態を保持するワーク
static WORD				g_wKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート状態を保持するワーク
static int				g_nKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

static DWORD			g_dwJoyCount;
static JOYINFOEX		g_joyState[NUM_JOY_MAX];
static DWORD			g_dwJoyButtonTrigger[NUM_JOY_MAX];
static DWORD			g_dwJoyButtonRelease[NUM_JOY_MAX];

static POINT			g_ptMouse;
static POINT			g_StandardMouse;
static POINT			g_NowMouse;
static const int		g_nMouseBtn[] = { VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2 };
static int				g_MouseNo;
static bool				g_PressMouse;

static DWORD			g_WindowMousePosX;
static DWORD			g_WindowMousePosY;

static XMFLOAT2			Mouse2;

WORD					KeyBottun[256];		//キーボードのキーコード配列
WORD					JoyBottun[31];
static LONG				Dpov;

#pragma comment(lib, "Xinput.lib")
#include "xinput.h" 
static WORD				g_wVibrationTime[2];
static XINPUT_VIBRATION vibration;


//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput()
{
	HRESULT hr = S_OK;

	// キーボードの初期化
	hr = InitKeyboard();

	// ゲームパッドの初期化
	if (SUCCEEDED(hr)) {
		hr = InitJoystick();
	}

	// マウスの初期化
	if (SUCCEEDED(hr)) {
		hr = InitMouse();
	}

	g_NowMouse = *GetMousePosition();
	g_NowMouse.x = g_NowMouse.x;
	g_NowMouse.y = g_NowMouse.y;
	g_StandardMouse.x = STANDARDMOUSEPOS_X;
	g_StandardMouse.y = STANDARDMOUSEPOS_Y;
	g_MouseNo = 0;
	Dpov = -1;
	return hr;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput()
{
	// マウスの終了処理
	UninitMouse();

	// ゲームパッドの終了処理
	UninitJoystick();

	// キーボードの終了処理
	UninitKeyboard();
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput()
{
	// キーボードの更新
	UpdateKeyboard();

	// ゲームパッドの更新
	UpdateJoystick();

	// マウスの更新
	UpdateMouse();
	Dpov = -1;
}

//=============================================================================
// キーボードの初期化処理
//=============================================================================
HRESULT InitKeyboard()
{
	HRESULT hr = S_OK;

	return hr;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	// (何もしない)
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr = S_OK;
	WORD wKeyState;

	// キーボードの状態を取得
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++) {
		wKeyState = GetAsyncKeyState(nCntKey);

		g_wKeyStateTrigger[nCntKey] = (g_wKeyState[nCntKey] ^ wKeyState) & wKeyState;
		g_wKeyStateRelease[nCntKey] = (g_wKeyState[nCntKey] ^ wKeyState) & ~wKeyState;
		g_wKeyStateRepeat[nCntKey] = g_wKeyStateTrigger[nCntKey];

		if (wKeyState & 0x8000) {
			g_nKeyStateRepeatCnt[nCntKey]++;
			if (g_nKeyStateRepeatCnt[nCntKey] >= 20) {
				g_wKeyStateRepeat[nCntKey] = wKeyState;
			}
		} else {
			g_nKeyStateRepeatCnt[nCntKey] = 0;
			g_wKeyStateRepeat[nCntKey] = 0;
		}

		g_wKeyState[nCntKey] = wKeyState;
	}

	return hr;
}

//=============================================================================
// ゲームパッドの初期化処理
//=============================================================================
HRESULT InitJoystick()
{
	GetJoyCount();

	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	g_wVibrationTime[0] = g_wVibrationTime[1] = -1;

	return S_OK;
}

//=============================================================================
// ゲームパッドの終了処理
//=============================================================================
void UninitJoystick()
{
	// (何もしない)
	//XInputEnable(false); // BOOL enable
}

//=============================================================================
// ゲームパッドの更新処理
//=============================================================================
HRESULT UpdateJoystick()
{
	HRESULT hr = S_OK;
	DWORD i;

	for (i = 0; i < g_dwJoyCount; ++i) {
		JOYINFOEX& ji = g_joyState[i];
		DWORD dwButtons = ji.dwButtons;
		ZeroMemory(&ji, sizeof(ji));
		ji.dwSize = sizeof(ji);
		ji.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(i, &ji) != JOYERR_NOERROR) {
			hr = E_FAIL;
			break;
		}
		g_dwJoyButtonTrigger[i] = (g_joyState[i].dwButtons ^ dwButtons) & g_joyState[i].dwButtons;
		g_dwJoyButtonRelease[i] = (g_joyState[i].dwButtons ^ dwButtons) & ~g_joyState[i].dwButtons;
	}
	for (; i < NUM_JOY_MAX; ++i) {
		JOYINFOEX& ji = g_joyState[i];
		ZeroMemory(&ji, sizeof(ji));
		g_dwJoyButtonTrigger[i] = 0;
		g_dwJoyButtonRelease[i] = 0;
	}

	bool reset = false;
	if (g_wVibrationTime[0] >= 0)
	{
		if (--g_wVibrationTime[0] == 0) {
			vibration.wRightMotorSpeed = 0;
			reset = true;
		}
	}
	if (g_wVibrationTime[1] >= 0)
	{
		if (--g_wVibrationTime[1] == 0) {
			vibration.wLeftMotorSpeed = 0;
			reset = true;
		}
	}
	if (reset)	XInputSetState(0, &vibration);

	return hr;
}

//=============================================================================
// マウスの初期化処理
//=============================================================================
HRESULT InitMouse()
{
	return S_OK;
}

//=============================================================================
// マウスの終了処理
//=============================================================================
void UninitMouse()
{
	// (何もしない)
}

//=============================================================================
// マウスの更新処理
//=============================================================================
HRESULT UpdateMouse()
{
	POINT pt;
	GetCursorPos(&pt);
	//ScreenToClient(GetMainWnd(), &pt);
	ScreenToClient(NULL, &pt);
	g_ptMouse = pt;
	MouseDirection();

	return S_OK;
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyPress(int nKey)
{
	return (g_wKeyState[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// キーボードのトリガ状態を取得
//=============================================================================
bool GetKeyTrigger(int nKey)
{
	return (g_wKeyStateTrigger[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyRepeat(int nKey)
{
	return (g_wKeyStateRepeat[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyRelease(int nKey)
{
	return (g_wKeyStateRelease[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// ゲームパッド接続数取得
//=============================================================================
DWORD GetJoyCount()
{
	JOYINFO	ji;
	DWORD dwCount = joyGetNumDevs();
	if (dwCount > NUM_JOY_MAX)
		dwCount = NUM_JOY_MAX;
	for (g_dwJoyCount = 0; g_dwJoyCount < dwCount; ++g_dwJoyCount) {
		if (joyGetPos(g_dwJoyCount, &ji) != JOYERR_NOERROR)
			break;
	}
	return g_dwJoyCount;
}

DWORD GetJoyCountSimple()
{
	return g_dwJoyCount;
}

//=============================================================================
// ゲームパッド情報取得
//=============================================================================
JOYINFOEX *GetJoyState(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) return nullptr;
	return &g_joyState[dwJoy];
}

//=============================================================================
// ゲームパッドX軸取得
//=============================================================================
LONG GetJoyX(DWORD dwJoy)
{
	if (GetJoyCountSimple() == 0)return 0L;
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)g_joyState[dwJoy].dwXpos - 0x08000;
}

//=============================================================================
// ゲームパッドY軸取得
//=============================================================================
LONG GetJoyY(DWORD dwJoy)
{
	if (GetJoyCountSimple() == 0)return 0L;
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)g_joyState[dwJoy].dwYpos - 0x08000;
}

//=============================================================================
// ゲームパッドZ軸取得
//=============================================================================
LONG GetJoyZ(DWORD dwJoy)
{
	if (GetJoyCountSimple() == 0)return 0L;
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)g_joyState[dwJoy].dwZpos - 0x08000;
}

//=============================================================================
// ゲームパッドU軸取得
//=============================================================================
LONG GetJoyU(DWORD dwJoy)
{
	if (GetJoyCountSimple() == 0)return 0L;
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)g_joyState[dwJoy].dwUpos - 0x08000;
}

//=============================================================================
// ゲームパッドV軸取得
//=============================================================================
LONG GetJoyV(DWORD dwJoy)
{
	if (GetJoyCountSimple() == 0)return 0L;
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)g_joyState[dwJoy].dwVpos - 0x08000;
}

//=============================================================================
// ゲームパッドR軸取得
//=============================================================================
LONG GetJoyR(DWORD dwJoy)
{
	if (GetJoyCountSimple() == 0)return 0L;
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)g_joyState[dwJoy].dwRpos - 0x08000;
}

//=============================================================================
// ゲームパッド ボタン情報取得
//=============================================================================
bool GetJoyButton(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) return false;
	return (g_joyState[dwJoy].dwButtons & (1 << dwBtn)) ? true : false;
	return false;
}

//=============================================================================
// ゲームパッド トリガ情報取得
//=============================================================================
bool GetJoyTrigger(DWORD dwJoy, DWORD dwBtn)
{
	//if (GetSceneNo() == SCENE_GAME && GetWorldMapMode())return (g_dwJoyButtonTrigger[dwJoy] & (1 << GetJoykode(dwBtn))) ? true : false;
	if (dwJoy >= NUM_JOY_MAX) return false;
	return (g_dwJoyButtonTrigger[dwJoy] & (1 << dwBtn)) ? true : false;
}

//=============================================================================
// ゲームパッド リリース情報取得
//=============================================================================
bool GetJoyRelease(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) return false;
	return (g_dwJoyButtonRelease[dwJoy] & (1 << dwBtn)) ? true : false;
}

LONG GetJoyPOV(DWORD dwJoy)
{
	LONG pov = g_joyState[dwJoy].dwPOV;
	return pov;
}

LONG GetJoyPOVTrigger(DWORD dwJoy)
{
	static LONG oldPOV = -1;
	LONG pov = g_joyState[dwJoy].dwPOV;
	if (oldPOV != pov)
	{
		oldPOV = pov;
		Dpov = pov;	//
		return pov;
	}
	return Dpov;
}

//=============================================================================
// マウス座標取得
//=============================================================================
POINT *GetMousePosition()
{
	return &g_ptMouse;
}

//=============================================================================
// マウス ボタン情報取得
//=============================================================================
bool GetMouseButton(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) return false;
	return GetKeyPress(g_nMouseBtn[dwBtn]);
}

//=============================================================================
// マウス トリガ情報取得
//=============================================================================
bool GetMouseTrigger(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) return false;
	return GetKeyTrigger(g_nMouseBtn[dwBtn]);
}

bool GetMousePress(DWORD dwBtn)
{
	if (GetMouseTrigger(dwBtn))g_PressMouse = true;
	if (GetMouseRelease(dwBtn))g_PressMouse = false;
	return g_PressMouse;
}

//=============================================================================
// マウス リリース情報取得
//=============================================================================
bool GetMouseRelease(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) return false;
	return GetKeyRelease(g_nMouseBtn[dwBtn]);
}

void SetWindowMousePos(const DWORD& PosX, const DWORD& PosY)
{
	g_WindowMousePosX = PosX;
	g_WindowMousePosY = PosY;
	g_WindowMousePosX -= SCREEN_CENTER_X;
	g_WindowMousePosY -= SCREEN_CENTER_Y;
	g_WindowMousePosY = g_WindowMousePosY * -1;
}

DWORD GetWindowMousePosX()
{
	return g_WindowMousePosX;
}

DWORD GetWindowMousePosY()
{
	return g_WindowMousePosY;
}


bool PInRight()
{
	if (GetKeyPress(VK_D)|| GetKeyPress(VK_RIGHT) || GetJoyButton(0, JOYBUTTON18))return true;
	return false;
}

bool PInLeft()
{
	if (GetKeyPress(VK_A) || GetKeyPress(VK_LEFT) || GetJoyButton(0, JOYBUTTON17))return true;
	return false;
}

bool PInUp()
{
	if (GetKeyPress(VK_W) || GetKeyPress(VK_UP) || GetJoyButton(0, JOYBUTTON19))return true;
	return false;
}

bool PInDown()
{
	if (GetKeyPress(VK_S) || GetKeyPress(VK_DOWN) || GetJoyButton(0, JOYBUTTON20))return true;
	return false;
}

bool PInB01()
{
	if (g_MouseNo % 5 == 2 || GetJoyButton(0, JOYBUTTON22))return true;
	return false;
}

bool PInB02()
{
	if (g_MouseNo % 5 == 1 || GetJoyButton(0, JOYBUTTON21))return true;
	return false;
}

bool PInB03()
{
	if (GetKeyPress(VK_R)|| GetJoyButton(0, JOYBUTTON3))return true;
	return false;
}

bool PInB04()
{
	if (GetKeyPress(VK_F) || GetJoyButton(0, 25))return true;
	return false;
}

bool PInB05()
{
	if (g_MouseNo / 5 == 1 || GetJoyButton(0, JOYBUTTON24))return true;
	return false;
}

bool PInB06()
{
	if (g_MouseNo / 5 == 0 || GetJoyButton(0, JOYBUTTON23))return true;
	return false;
}

bool PInB07()
{
	if (GetMouseButton(MOUSEBUTTON_L) || GetJoyButton(0, JOYBUTTON1))return true;
	return false;
}

bool PInB08()
{
	return false;
}

bool TInB01()
{
	if(GetKeyTrigger(VK_SPACE) || GetJoyButton(0, JOYBUTTON2))return true;
	return false;
}

bool TInB02()
{
	if (GetMouseTrigger(MOUSEBUTTON_R))return true;
	return false;
}

bool RInB02()
{
	return false;
}

int  MouseDirection()
{
	g_NowMouse = *GetMousePosition();
	Mouse2.x = (float)abs(g_StandardMouse.x - g_NowMouse.x);
	Mouse2.y = (float)abs(g_StandardMouse.y - g_NowMouse.y);
	if (g_StandardMouse.x - g_NowMouse.x > MOUSESENSITIVITY)
	{
		if (g_StandardMouse.y - g_NowMouse.y > MOUSESENSITIVITY)g_MouseNo = 1;
		else if (g_StandardMouse.y - g_NowMouse.y < -MOUSESENSITIVITY)g_MouseNo = 6;
		else g_MouseNo = 11;
	}
	else if (g_StandardMouse.x - g_NowMouse.x < -MOUSESENSITIVITY)
	{
		if (g_StandardMouse.y - g_NowMouse.y > MOUSESENSITIVITY)g_MouseNo = 2;
		else if (g_StandardMouse.y - g_NowMouse.y < -MOUSESENSITIVITY)g_MouseNo = 7;
		else g_MouseNo = 12;
	}
	else
	{
		if (g_StandardMouse.y - g_NowMouse.y > MOUSESENSITIVITY)g_MouseNo = 3;

		else if (g_StandardMouse.y - g_NowMouse.y < -MOUSESENSITIVITY)g_MouseNo = 8;
		else g_MouseNo = 13;
	}
	//g_StandardMouse = g_NowMouse;
	return g_MouseNo;
}

void ResetOperation()
{
	for (int i = 0; i < 256; i++)
	{
		KeyBottun[i] = (WORD)(i + 1);
	}
}

void ResetJOperation()
{
	for (int i = 0; i < 31; i++)
	{
		JoyBottun[i] = (WORD)(i);
	}
}

WORD GetKeykode(int no)
{
	return KeyBottun[no-1];
}

WORD GetJoykode(int no)
{
	return JoyBottun[no];

}

WORD GetTrigerKeyNo()
{
	for (int i = 0; i < 256; i++)
	{
		if (GetKeyRelease(i + 1))return (i + 1);
	}
	return 0;
}


WORD GetTrigerTestKeyNo()
{
	for (int i = 0; i < 256; i++)
	{
		if (GetKeyPress(i + 1))return (i + 1);
	}
	return 0;
}

WORD GetTrigerJoyNo()
{
	for (int i = 0; i < 31; i++)
	{
		if (GetJoyButton(0,i))return (i);
	}
	return 999;
}

void SetKeyNo(int KBno, WORD Kno)
{
	int ChangeNo = KBno - 1;
	WORD ChangeKeyNo;
	for (int i = 0; i < 256; i++)
	{
		if (KeyBottun[i] == Kno)ChangeNo = i;
	}
	if (ChangeNo == (KBno - 1))return;
	if (Kno == VK_ESCAPE)return;
	ChangeKeyNo = KeyBottun[KBno - 1];
	KeyBottun[KBno-1] = Kno;
	KeyBottun[ChangeNo] = ChangeKeyNo;
}

void SetJoyNo(int KBno, WORD Kno)
{
	int ChangeJNo = KBno;
	WORD ChangeJoyNo;
	for (int i = 0; i < 31; i++)
	{
		if (JoyBottun[i] == Kno)ChangeJNo = i;
	}
	if (ChangeJNo == (KBno))return;
	//if (Kno == VK_ESCAPE)return;
	ChangeJoyNo = JoyBottun[KBno];
	JoyBottun[KBno] = Kno;
	JoyBottun[ChangeJNo] = ChangeJoyNo;
}

JOYINFOEX aaaa()
{
	return g_joyState[0];
}

XMFLOAT2 GetMousePNo()
{
	Mouse2.x = 1.0f + (Mouse2.x / 3.0f) + abs(GetJoyU(0) / 1000);
	Mouse2.y = 1.0f + (Mouse2.y / 3.0f) + abs(GetJoyR(0) / 1000);
	return Mouse2;
}

// length: 0-65535
void SetVibration(int left/*=1*/, int size/* = 65535*/, int frame/*=8*/)
{
	if (left) {
		vibration.wLeftMotorSpeed += size; // use any value between 0-65535 here
	}
	else {
		vibration.wRightMotorSpeed += size; // use any value between 0-65535 here
	}
	g_wVibrationTime[left] = frame;
	/*for (int i = 0; i < 10; i++)
	{
		XInputSetState(0, &vibration);
	}*/
	XInputSetState(0, &vibration);
}

void ResetVibration()
{
	//XInputEnable(false); // BOOL enable

}