//=============================================================================
//
// 入力処理 [input.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)				// キー最大数
#define NUM_JOY_MAX			(32)				// ゲームパッド最大数
#define STANDARDMOUSEPOS_X	(GetSystemMetrics(SM_CXSCREEN)/2)
#define STANDARDMOUSEPOS_Y	(GetSystemMetrics(SM_CYSCREEN)/2)
#define MOUSESENSITIVITY	(3)

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOUSEBUTTON_L	0
#define MOUSEBUTTON_R	1
#define MOUSEBUTTON_M	2
#define MOUSEBUTTON_X1	3
#define MOUSEBUTTON_X2	4

//ちょっくら調べた結果マウスの操作も最終的に「GetKeyPress」に飛ぶみたいなので
//僕のでは仮想キーコードに対応した「GetKeyPress」だけを使ったプログラムで行きます
//	マウス(GetKeyPress用番号)
//	VK_LBUTTON	マウスの左ボタン		1
//	VK_RBUTTON	マウスの右ボタン		2
//	VK_MBUTTON	マウスの中央ボタン		3
//	VK_XBUTTON1	マウスの第1拡張ボタン	5
//	VK_XBUTTON2	マウスの第2拡張ボタン	6

#define VK_0	'0'//	48
#define VK_1	'1'//	│
#define VK_2	'2'//	│
#define VK_3	'3'//	│
#define VK_4	'4'//	│
#define VK_5	'5'//	│
#define VK_6	'6'//	│
#define VK_7	'7'//	│
#define VK_8	'8'//	↓
#define VK_9	'9'//	57

#define VK_A	'A'//	65
#define VK_B	'B'//	│
#define VK_C	'C'//	│
#define VK_D	'D'//	│
#define VK_E	'E'//	│
#define VK_F	'F'//	│
#define VK_G	'G'//	│
#define VK_H	'H'//	│
#define VK_I	'I'//	│
#define VK_J	'J'//	│
#define VK_K	'K'//	│
#define VK_L	'L'//	│
#define VK_M	'M'//	│
#define VK_N	'N'//	│
#define VK_O	'O'//	│
#define VK_P	'P'//	│
#define VK_Q	'Q'//	│
#define VK_R	'R'//	│
#define VK_S	'S'//	│
#define VK_T	'T'//	│
#define VK_U	'U'//	│
#define VK_V	'V'//	│
#define VK_W	'W'//	│
#define VK_X	'X'//	│
#define VK_Y	'Y'//	↓
#define VK_Z	'Z'//	90

#define JOYBUTTON1	0
#define JOYBUTTON2	1
#define JOYBUTTON3	2
#define JOYBUTTON4	3
#define JOYBUTTON5	4
#define JOYBUTTON6	5
#define JOYBUTTON7	6
#define JOYBUTTON8	7
#define JOYBUTTON9	8
#define JOYBUTTON10	9
#define JOYBUTTON11	10	//十字←
#define JOYBUTTON12	11	//十字→
#define JOYBUTTON13	12	//十字↑
#define JOYBUTTON14	13	//十字↓
#define JOYBUTTON15	14	//L2
#define JOYBUTTON16	15	//R2
#define JOYBUTTON17	16	//左スティック←
#define JOYBUTTON18	17	//左スティック→
#define JOYBUTTON19	18	//左スティック↑
#define JOYBUTTON20	19	//左スティック↓
#define JOYBUTTON21	20	//右スティック←
#define JOYBUTTON22	21	//右スティック→
#define JOYBUTTON23	22	//右スティック↑
#define JOYBUTTON24	23	//右スティック↓
#define JOYBUTTON25	24	
#define JOYBUTTON26	25	
#define JOYBUTTON27	26	
#define JOYBUTTON28	27	
#define JOYBUTTON29	28	
#define JOYBUTTON30	29	
#define JOYBUTTON31	30
#define JOYBUTTON32	31

#define JOYSTICKID3		2
#define JOYSTICKID4		3
#define JOYSTICKID5		4
#define JOYSTICKID6		5
#define JOYSTICKID7		6
#define JOYSTICKID8		7
#define JOYSTICKID9		8
#define JOYSTICKID10	9
#define JOYSTICKID11	10
#define JOYSTICKID12	11
#define JOYSTICKID13	12
#define JOYSTICKID14	13
#define JOYSTICKID15	14
#define JOYSTICKID16	15

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput();
void UninitInput();
void UpdateInput();

bool GetKeyPress(int nKey);
bool GetKeyTrigger(int nKey);
bool GetKeyRelease(int nKey);
bool GetKeyRepeat(int nKey);

DWORD GetJoyCount();
DWORD GetJoyCountSimple();
JOYINFOEX *GetJoyState(DWORD dwJoy);
LONG GetJoyX(DWORD dwJoy);
LONG GetJoyY(DWORD dwJoy);
LONG GetJoyZ(DWORD dwJoy);
LONG GetJoyU(DWORD dwJoy);
LONG GetJoyV(DWORD dwJoy);
LONG GetJoyR(DWORD dwJoy);
bool GetJoyButton(DWORD dwJoy, DWORD dwBtn);
bool GetJoyTrigger(DWORD dwJoy, DWORD dwBtn);
bool GetJoyRelease(DWORD dwJoy, DWORD dwBtn);
LONG GetJoyPOV(DWORD dwJoy);
LONG GetJoyPOVTrigger(DWORD dwJoy);

POINT *GetMousePosition();
bool GetMouseButton(DWORD dwBtn);
bool GetMouseTrigger(DWORD dwBtn);
bool GetMousePress(DWORD dwBtn);
bool GetMouseRelease(DWORD dwBtn);
void SetWindowMousePos(const DWORD&, const DWORD&);
DWORD GetWindowMousePosX();
DWORD GetWindowMousePosY();
void ResetOperation();		//キーボードボタン初期化
void ResetJOperation();
WORD GetKeykode(int no);	//もともとの標準のキー番号を送ると設定されているキー番号が返ってくる
WORD GetJoykode(int no);
WORD GetTrigerKeyNo();		//押されているキー番号を返す
WORD GetTrigerTestKeyNo();
WORD GetTrigerJoyNo();
void SetKeyNo(int KBno, WORD Kno);
void SetJoyNo(int KBno, WORD Kno);

//頭文字PはPress,TはTrigger.RはRelease
bool PInRight();		//D.RIGHT
bool PInLeft();			//A.LEFT
bool PInUp();			//W.UP
bool PInDown();			//S.DOWN
bool PInB01();			//E.マウス右移動
bool PInB02();			//Q.マウス左移動
bool PInB03();			//R
bool PInB04();			//F
bool PInB05();			//T.マウス上移動
bool PInB06();			//G.マウス下移動
bool PInB07();			//マウス左ボタン
bool PInB08();			//
bool TInB01();			//space
bool TInB02();			//マウス右ボタン
bool RInB02();			//
int  MouseDirection();	//マウスの移動取得

XMFLOAT2 GetMousePNo();

JOYINFOEX aaaa();

void SetVibration(int left = 1, int length = 65535, int frame = 8);