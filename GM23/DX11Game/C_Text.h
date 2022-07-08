#pragma once
#include "main.h"
typedef struct
{
	ID3D11ShaderResourceView*	pTexture;
	XMFLOAT3		Position;		//座標
	XMFLOAT2		Size;			//サイズ
	float			Angle;		//回転角度
	XMFLOAT3		vel;
	XMFLOAT2		Scale;
	XMFLOAT2		TexCoord;		//テクスチャ座標(ポリゴンの左上)
	XMFLOAT2		TexFrameSize; //テクスチャを張り付けるサイズ
	float			Alfa;
	float			AlfaAd;
	float			AngleAd;		//回転角度
	int				State;
}tText;

class CText
{
public:
	tText		g_text;
	HRESULT InitCText(char* text, XMFLOAT2 size, XMFLOAT3 pos);	//初期化
	void	UninitCText();	//終了
	void	UpdateCText();	//更新
	void	DrawCText();	//描画
};
