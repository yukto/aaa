#pragma once
#include "main.h"

typedef struct _tDATA2 {
	int				HP;				//体力
	int				Attack;			//攻撃力
	int				Defense;		//防御力
	int				Speed;			//速さ
	int				INT;			//賢さ
	int				EvasionRate;	//回避率
	int				Guts;			//根性
} _tDATA2;

//プロトタイプ宣言
HRESULT InitBattle();
void UninitBattle();
void UpdateBattle();
void DrawBattle();
void Draw2DBattle();