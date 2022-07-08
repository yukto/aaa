// collision.h
// 当たり判定用

#pragma once

#include "main.h"

void Collision();	// 当たり判定まとめ
int HS_TitleMouseCollision(int No);

// バウンディングボックス(BB)
bool CollisionBB(
	XMFLOAT2* pCenter1, XMFLOAT2* pSize1,
	XMFLOAT2* pCenter2, XMFLOAT2* pSize2 );

// バウンディングサークル(BC)
bool CollisionBC(
	XMFLOAT2* pCenter1, float fRadius1,
	XMFLOAT2* pCenter2, float fRadius2 );
bool TextCollision(XMFLOAT2 pos, XMFLOAT2 size, int mode/*マウスなら0*/);


