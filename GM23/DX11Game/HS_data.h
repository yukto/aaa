#pragma once
typedef struct _tDATA {
	int				HP;				//�̗�
	int				Attack;			//�U����
	int				Defense;		//�h���
	int				Speed;			//����
	int				INT;			//����
	int				EvasionRate;	//���
	int				Guts;			//����
} _tDATA;

int InitData(int no);
void DataSave();
_tDATA Getdata(int no);