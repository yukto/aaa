//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

#include <xaudio2.h>
// Windows7�̏ꍇ�͏�L���폜���Ĉȉ��ɒu������.
//#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h>

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM001 = 0,		// BGM0
	SOUND_LABEL_BGM002,
	SOUND_LABEL_BGM003,
	SOUND_LABEL_BGM004,
	SOUND_LABEL_BGM005,
	SOUND_LABEL_BGMMAX,
	SOUND_LABEL_SE_01,
	SOUND_LABEL_SE_02,
	SOUND_LABEL_SE_03,
	SOUND_LABEL_SE_04,
	SOUND_LABEL_SE_05,
	SOUND_LABEL_SE_MAX,
	SOUND_LABEL_VOICE001,
	SOUND_LABEL_VOICE002,
	SOUND_LABEL_VOICE003,
	SOUND_LABEL_VOICE004,
	SOUND_LABEL_VOICE005,
	SOUND_LABEL_VOICE006,
	SOUND_LABEL_VOICEMAX,

	SOUND_LABEL_MAX,			// �o�^���̎����ݒ�
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);	// �Đ�

void StopSound(SOUND_LABEL label);		// 1��~
void StopSound(void);					// �S����~
void PauseSound(void);				// �ꎞ��~
void ResumeSound(void);				// �ĊJ
void ResumeSoundOne(int no);

void SetVolume(float fVol);				// ���ʒ���
void SetVolumeOne(float fVol);
void SetSourceVolumeAll(float fVol, int Sno);
void SetSourceVolume(float fVol, int no);
float GetSoundVolume(int a);
void ResetSound();
float GetSoundLevel(int no);
#endif
