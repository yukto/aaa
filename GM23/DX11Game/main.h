//=============================================================================
//
// ���C������ [main.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <mmsystem.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "resource.h"
#include "D2DDrawMng.h"
#include "D2DText.h"

#pragma warning(disable:4996)

// �{���̓w�b�_�ɏ����Ȃ������ǂ�
using namespace DirectX;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){(x)->Release();x=nullptr;}}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if(x){delete(x);x=nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) {if(x){delete[](x);x=nullptr;}}
#endif

#define SCREEN_WIDTH	(1280)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH/2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT/2)	// �E�C���h�E�̒��S�x���W

#define	NUM_VERTEX		(4)					// ���_��
#define	NUM_POLYGON		(2)					// �|���S����

#define SinDeg(degree)	(sinf(XMConvertToRadians(degree)))
#define CosDeg(degree)	(cosf(XMConvertToRadians(degree)))

//�񋓑̒�`
enum E_TYPE_SCENE
{
	SCENE_TITLE = 0,	//�^�C�g�����
	SCENE_GAME,
	SCENE_CLEAR,
	SCENE_CONFIG,
	SCENE_MENU,
	SCENE_BATTLE,

	MAX_SCENE			//������͕K����ԍŌ�
};

enum EBlendState {
	BS_NONE = 0,							// ��������������
	BS_ALPHABLEND,							// ����������
	BS_ADDITIVE,							// ���Z����
	BS_SUBTRACTION,							// ���Z����

	MAX_BLENDSTATE
};

enum ECullMode {
	CULLMODE_NONE = 0,						// �J�����O���Ȃ�
	CULLMODE_CW,							// �O�ʃJ�����O
	CULLMODE_CCW,							// �w�ʃJ�����O

	MAX_CULLMODE
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ���_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
typedef struct {
	XMFLOAT3 vtx;		// ���_���W
	XMFLOAT4 diffuse;	// �g�U���ˌ�
	XMFLOAT2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

// ���_�t�H�[�}�b�g( ���_���W[3D] / �@���x�N�g�� / ���ˌ� / �e�N�X�`�����W )
typedef struct {
	XMFLOAT3 vtx;		// ���_���W
	XMFLOAT3 nor;		// �@���x�N�g��
	XMFLOAT4 diffuse;	// �g�U���ˌ�
	XMFLOAT2 tex;		// �e�N�X�`�����W
} VERTEX_3D;

typedef struct {
	int nPatNo;    //�\���p�^�[���ԍ�
	int nCount;    //�\���t���[����
}ANIM_PAT;

class SCENE
{
public:
	HRESULT SInit();
	void SUninit();
	void SUpdate();
	void SDarw();
	void SDraw2D();
private:

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �O���錾
namespace F_lib_Render
{
	class D2DText;
	class D2DTextMng;
}

HWND GetMainWnd();
HINSTANCE GetInstance();
ID3D11Device* GetDevice();
IDXGISwapChain* GetSwapChain();
ID3D11DeviceContext* GetDeviceContext();
void SetZBuffer(bool bEnable);
void SetZWrite(bool bEnable);
void SetBlendState(int nBlendState);
void SetCullMode(int nCullMode);
void StartSceneChange(E_TYPE_SCENE next);
E_TYPE_SCENE GetCurrentScene();
int gettestnono();
F_lib_Render::D2DText*		GetD2DText();
F_lib_Render::D2DTextMng*	GetTextMng();
