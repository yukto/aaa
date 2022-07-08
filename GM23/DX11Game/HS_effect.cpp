//=============================================================================
//
// DirectX11ベース [explosion.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================

//*******インクルード************
#include "HS_effect.h"
#include <time.h>
#define EXPLOSION_TEXTURENAME4		_T("data/texture/HS/water.png")		// ポリゴンに表示させる画像

//================================
//			初期化
//================================
HRESULT GameEffect::HS_InitExplosion(char* text,XMFLOAT2 size,XMFLOAT2 frame,int no)
{
	HRESULT hr = S_OK;

	// テクスチャ読み込み
	ID3D11Device*	pDevice = GetDevice();
	hr = CreateTextureFromFile(pDevice, text, &g_pTexture);

	EXPLOSION_FRAME = frame;

	for (int i = 0; i < (int)frame.x * (int)frame.y; i++)
	{
		g_animPat[0][i].nPatNo = i;
		g_animPat[0][i].nCount = no;
	}

	//パラメータの初期化
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		g_Explosion[i].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_Explosion[i].Size = XMFLOAT2(size.x, size.y);
		g_Explosion[i].Angle = 0.0f;
		g_Explosion[i].vel = XMFLOAT2(0.0f, 0.0f);
		g_Explosion[i].bUse = false;	//最初は未使用状態
		g_Explosion[i].Scale = XMFLOAT2(1.0f, 1.0f);			// 拡大縮小
		g_Explosion[i].nDir = 0;		// 方向
		g_Explosion[i].nAnimNo = 0;		// 表示情報No.
		g_Explosion[i].nCount = g_animPat[0][g_Explosion[i].nAnimNo].nCount;			// 残りフレーム数
	}
	return hr;
}

//================================
//			終了
//================================
void GameEffect::HS_UninitExplosion()
{
	// テクスチャ後片づけ
	SAFE_RELEASE(g_pTexture);
}


//================================
//			更新
//================================
void GameEffect::HS_UpdateExplosion(void)
{
		//敵の配列を順番に回して、更新（移動）させる
		for (int i = 0; i < MAX_EXPLOSION; i++)
		{
			//出ていない敵は処理しない
			if (g_Explosion[i].bUse == false)
			{
				continue;
			}

			//移動
			//アニメーション情報の更新
			g_Explosion[i].nCount--;		//残りカウントを減らす
			if (g_Explosion[i].nCount <= 0)
			{
				g_Explosion[i].nAnimNo++;		//次の絵に進める
				if (g_animPat[g_Explosion[i].nDir][g_Explosion[i].nAnimNo].nPatNo < 0)
				{		//番兵を参照したら
					g_Explosion[i].bUse = false;	//先頭に戻す
				}
				//カウンタを次の絵の表示フレーム数に設定
				g_Explosion[i].nCount = g_animPat[g_Explosion[i].nDir][g_Explosion[i].nAnimNo].nCount;
			}
		}
}


//================================
//			描画
//================================
void GameEffect::HS_DrawExplosion()
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		//未発射の敵は表示しない
		if (g_Explosion[i].bUse == false)
		{
			continue;
		}

		//ポリゴンの情報設定		ここ
		SetPolygonAngle(g_Explosion[i].Angle);						//degree(デグリー)値(0~360°)	
		SetPolygonPos(g_Explosion[i].Position.x, g_Explosion[i].Position.y);
		SetPolygonSize(g_Explosion[i].Size.x, g_Explosion[i].Size.y);
													//←→radian(ラジアン)値(0~2π)

		SetPolygonFrameSize(1.0f / EXPLOSION_FRAME.x, 1.0f / EXPLOSION_FRAME.y);// 横幅縦幅
		int u = g_animPat[g_Explosion[i].nDir][g_Explosion[i].nAnimNo].nPatNo % (int)EXPLOSION_FRAME.x;
		int v = g_animPat[g_Explosion[i].nDir][g_Explosion[i].nAnimNo].nPatNo / (int)EXPLOSION_FRAME.x;
		SetPolygonUV(u / EXPLOSION_FRAME.x, v / EXPLOSION_FRAME.y);	// 左上のUV座標
		SetPolygonTexture(g_pTexture);// テクスチャ指定


		// ポリゴンの描画処理
		ID3D11DeviceContext*	pDeviceContext = GetDeviceContext();
		DrawPolygon(pDeviceContext);
		SetPolygonAngle(0.0f);
	}
}

//敵の発射
//pos : 指定された場所
void GameEffect::HS_SetExplosion(XMFLOAT3 pos, bool bAngle)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		//発射されている敵は発射できない
		if (g_Explosion[i].bUse == true)
		{
			continue;
		}

		g_Explosion[i].bUse = true;		//発射状態
		g_Explosion[i].Position = pos;
		if(bAngle)g_Explosion[i].Angle = (float)(rand() % 360);
		else g_Explosion[i].Angle = 0.0f;
		g_Explosion[i].nAnimNo = 0;
		g_Explosion[i].nCount = g_animPat[0][g_Explosion[i].nAnimNo].nCount;
		g_Explosion[i].nDir = 0;

		break;
	}
}
//
//void GameEffect::HS_BreakExplosion(int no)
//{
//	g_Explosion[no].bUse = false;
//}