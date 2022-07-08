#include "main.h"
#include "HS_data.h"
#include <stdio.h>

_tDATA MonsterData[7];

int InitData(int no)
{
	FILE* fp;
	switch (no)
	{
	case 1:
		if ((fp = fopen("savedata/player1_1/monsterdata.dat", "rb")) != NULL)
		{
			fread(&MonsterData[no], sizeof(_tDATA), 1, fp);
			fclose(fp);
			fp = NULL;
		}
		else return no;
		break;
	case 2:
		if ((fp = fopen("savedata/player1_2/monsterdata.dat", "rb")) != NULL)
		{
			fread(&MonsterData[no], sizeof(_tDATA), 1, fp);
			fclose(fp);
			fp = NULL;
		}
		else return no;
		break;
	case 3:
		if ((fp = fopen("savedata/player1_3/monsterdata.dat", "rb")) != NULL)
		{
			fread(&MonsterData[no], sizeof(_tDATA), 1, fp);
			fclose(fp);
			fp = NULL;
		}
		else return no;
		break;
	case 4:
		if ((fp = fopen("savedata/player2_1/monsterdata.dat", "rb")) != NULL)
		{
			fread(&MonsterData[no], sizeof(_tDATA), 1, fp);
			fclose(fp);
			fp = NULL;
		}
		else return no;
		break;
	case 5:
		if ((fp = fopen("savedata/player2_2/monsterdata.dat", "rb")) != NULL)
		{
			fread(&MonsterData[no], sizeof(_tDATA), 1, fp);
			fclose(fp);
			fp = NULL;
		}
		else return no;
		break;
	case 6:
		if ((fp = fopen("savedata/player2_3/monsterdata.dat", "rb")) != NULL)
		{
			fread(&MonsterData[no], sizeof(_tDATA), 1, fp);
			fclose(fp);
			fp = NULL;
		}
		else return no;
		break;
	default:
		break;
	}
	return true;
}

void DataSave()
{
	//ÉtÉ@ÉCÉãÇ…èëÇ´çûÇ›
	FILE* fp;
	if ((fp = fopen("savedata/make/monsterdata.dat", "wb")) != NULL)
	{
		fwrite(&MonsterData[0], sizeof(_tDATA), 1, fp);
		fclose(fp);
	}
}

_tDATA Getdata(int no)
{
	return MonsterData[no];
}