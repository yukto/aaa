#pragma once

#include"main.h"

typedef struct _tDATA {
	long				WhiteWin1[1000000][60];
	long				BlackWin1[1000000][60];
	long				Wcount;
	long				Bcount;
} tDATA;

void InitData();
int GetBattleData(int a, int i, int color);
void DataSave();
void SaveBattleData(int no, int no2, int no3);
tDATA GetDataCPU();