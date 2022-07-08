#pragma once
typedef struct _tDATA {
	int				HP;				//‘Ì—Í
	int				Attack;			//UŒ‚—Í
	int				Defense;		//–hŒä—Í
	int				Speed;			//‘¬‚³
	int				INT;			//Œ«‚³
	int				EvasionRate;	//‰ñ”ğ—¦
	int				Guts;			//ª«
} _tDATA;

int InitData(int no);
void DataSave();
_tDATA Getdata(int no);