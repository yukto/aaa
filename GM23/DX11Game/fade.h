//=============================================================================
//
// �t�F�[�h���� [fade.h]
//
//=============================================================================
#pragma once

#include "main.h"

// �}�N����`
enum E_FADE 
{
	E_FADE_NONE,	// �t�F�[�h���Ă��Ȃ�
	E_FADE_IN,		// �t�F�[�h�C����
	E_FADE_LOAD,
	E_FADE_OUT,		// �t�F�[�h�A�E�g��
	E_FADE_MAX
};

// �v���g�^�C�v�錾
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void StartFade( E_TYPE_SCENE stateNext, int nFrame);	// �t�F�[�h�J�n
E_FADE GetFade();		// �t�F�[�h���H
float GetFadeAlpha();