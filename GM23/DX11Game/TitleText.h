#pragma once
#include "main.h"
#include "C_Text.h"
class Titletxet :public CText {
public:
	float Scroll;
	float Scroll1;
	void Update();
};

HRESULT InitTitleText();
void UninitTitleText();
void UpdateTitleText();
void DrawTitleText(int no);