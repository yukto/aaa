#pragma once
#include "main.h"

//プロトタイプ宣言
HRESULT InitTitle();
void UninitTitle();
void UpdateTitle();
void DrawTitle();
void Draw2DTitle();
int GetMenuNo();
int GetMenuSwitch();
void SetMenuSwitch(int no);