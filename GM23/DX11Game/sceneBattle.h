#pragma once
#include "main.h"

typedef struct _tDATA2 {
	int				HP;				//�̗�
	int				Attack;			//�U����
	int				Defense;		//�h���
	int				Speed;			//����
	int				INT;			//����
	int				EvasionRate;	//���
	int				Guts;			//����
} _tDATA2;

//�v���g�^�C�v�錾
HRESULT InitBattle();
void UninitBattle();
void UpdateBattle();
void DrawBattle();
void Draw2DBattle();