// collision.h
// �����蔻��p

#pragma once

#include "main.h"

void Collision();	// �����蔻��܂Ƃ�
int HS_TitleMouseCollision(int No);

// �o�E���f�B���O�{�b�N�X(BB)
bool CollisionBB(
	XMFLOAT2* pCenter1, XMFLOAT2* pSize1,
	XMFLOAT2* pCenter2, XMFLOAT2* pSize2 );

// �o�E���f�B���O�T�[�N��(BC)
bool CollisionBC(
	XMFLOAT2* pCenter1, float fRadius1,
	XMFLOAT2* pCenter2, float fRadius2 );
bool TextCollision(XMFLOAT2 pos, XMFLOAT2 size, int mode/*�}�E�X�Ȃ�0*/);


