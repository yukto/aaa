// collision.cpp
// �����蔻���������
#include "collision.h"
#include "text.h"
#include "input.h"

// �����蔻��܂Ƃ�
void Collision()
{

}

int HS_TitleMouseCollision(int No)
{
	int no = -1;
	no = -1;
	switch (No)
	{
	case 0:
		for (int i = 0; i < 11; i++)
		{
			if (i == 5)continue;
			if (i < 7)
			{
				if (abs((LONG)(GetTextData(i).g_Position.x - (int)GetWindowMousePosX())) <= GetTextData(i).g_Size.x / 2 &&
					abs((LONG)(GetTextData(i).g_Position.y + GetMenuPos() - (int)GetWindowMousePosY())) <= GetTextData(i).g_Size.y / 2)
				{
					if (i < 5 && (abs((LONG)((GetTextData(i).g_Position.x - (int)GetWindowMousePosX()) * (GetTextData(i).g_Position.x - (int)GetWindowMousePosX()))) +
						abs((LONG)(((GetTextData(i).g_Position.y - (int)GetWindowMousePosY())) * (GetTextData(i).g_Position.y - (int)GetWindowMousePosY()))) <= 2500))
					{
						if (no == -1)no = i;
					}
					else if (no == -1)no = i;
				}
			}
			else
			{
				if (abs((LONG)(GetTextData(i).g_Position.x - (int)GetWindowMousePosX())) <= GetTextData(i).g_Size.x / 2 &&
					abs((LONG)(GetTextData(i).g_Position.y - (int)GetWindowMousePosY())) <= GetTextData(i).g_Size.y / 2)
				{
					if (i < 5 && (abs((LONG)((GetTextData(i).g_Position.x - (int)GetWindowMousePosX()) * (GetTextData(i).g_Position.x - (int)GetWindowMousePosX()))) +
						abs((LONG)(((GetTextData(i).g_Position.y - (int)GetWindowMousePosY())) * (GetTextData(i).g_Position.y - (int)GetWindowMousePosY()))) <= 2500))
					{
						if (no == -1)no = i;
					}
					else if (no == -1)no = i;
				}
			}
		}
		break;
	default:
		for (int i = 0; i < 2; i++)
		{

		}
		break;
	}
	
	return no;
}

// �o�E���f�B���O�{�b�N�X
// ��`���m�̓����蔻��
bool CollisionBB( XMFLOAT2 * pCenter1, XMFLOAT2 * pSize1, XMFLOAT2 * pCenter2, XMFLOAT2 * pSize2 )
{
	if( pCenter1->x + pSize1->x >= 
		pCenter2->x - pSize2->x && 
		pCenter1->x - pSize1->x <=
		pCenter2->x + pSize2->x )
	{	// X�������������Ă���
		if( pCenter1->y + pSize1->y >=
			pCenter2->y - pSize2->y &&
			pCenter1->y - pSize1->y <=
			pCenter2->y + pSize2->y )
		{	// Y�������������Ă���
			return true;
		}
	}
	// ������Ȃ�����
	return false;
}

// �o�E���f�B���O�T�[�N��
// �~���m�̓����蔻��
bool CollisionBC( XMFLOAT2 * pCenter1, float fRadius1, XMFLOAT2 * pCenter2, float fRadius2 )
{
	float fx = pCenter1->x - pCenter2->x;
	float fy = pCenter1->y - pCenter2->y;
	float len = fx * fx + fy * fy;
	float fr = fRadius1 + fRadius2;
	if( len < fr * fr )
	{
		return true;	// ��������
	}

	return false;		// �������ĂȂ�
}

bool TextCollision(XMFLOAT2 pos, XMFLOAT2 size, int mode/*�}�E�X�Ȃ�0*/)
{
	switch (mode)
	{
	case(0):
		if ((pos.x + (size.x / 2.0f)) > (int)GetWindowMousePosX() && (pos.x - (size.x / 2.0f)) < (int)GetWindowMousePosX())
		{
			if ((pos.y + (size.y / 2.0f)) > (int)GetWindowMousePosY() && (pos.y - (size.y / 2.0f)) < (int)GetWindowMousePosY())
			{
				return true;
				break;
			}
		}
		return false;
		break;
	default:
		return false;
		break;
	}
}