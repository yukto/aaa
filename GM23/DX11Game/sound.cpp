//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#define USE_SOUND
#include "sound.h"
#include "input.h"
#if (_WIN32_WINNT >= 0x0602)
#pragma comment(lib, "xaudio2.lib")
#endif

#define SOUNDMAXPERCENT		(1.0f)
#define SOUNDSTARTPERCENT	(0.4f)

//*****************************************************************************
// �p�����[�^�\���̒�`
//*****************************************************************************
typedef struct
{
	LPCWSTR	pFilename;		// �t�@�C����
	BYTE	nCntLoop;		// ���[�v�J�E���g
} SOUNDPARAM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
#ifdef USE_SOUND
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
static float SoundSet[4];	//0���S�̂ł���ȊO��BGM,SE,VOICE�ɂȂ��Ă���
static XMFLOAT4 Soundbuttonplace[12];
static int Mno;
#endif

// �e���f�ނ̃p�����[�^
SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	{L"data/sound/bgm/bgm0.wav", -1}, // BGM0( -1�̓��[�v�Đ�,0�͈�񂾂��Đ�)
	{L"data/sound/bgm/bgm1.wav", -1}, 
	{L"data/sound/bgm/bgm2.wav", -1}, 
	{L"data/sound/bgm/bgm3.wav", -1}, 
	{L"data/sound/bgm/bgm4.wav", -1}, 
	{L"data/sound/bgm/bgm5.wav", -1}, // BGMMAX(�Œ�)
	{L"data/sound/se/decide13.wav", 0 },
	{L"data/sound/se/kougekikaihi-02.wav", 0 },
	{L"data/sound/se/�V���b�v����������.wav", 0 },
	{L"data/sound/se/se1.wav", 0 },
	{L"data/sound/se/se2.wav", 0 },
	{L"data/sound/se/se3.wav", 0 },// SEMMAX(�Œ�)
	{L"data/sound/voice/voice1_01.wav", 0 },
	{L"data/sound/voice/voice1_02.wav", 0 },
	{L"data/sound/voice/voice1_03.wav", 0 },
	{L"data/sound/voice/voice1_04.wav", 0 },
	{L"data/sound/voice/voice1_05.wav", 0 },
	{L"data/sound/voice/voice1_06.wav", 0 },
	{L"data/sound/voice/voice1_07.wav", 0 },// VOICEMMAX(�Œ�)
};

//=============================================================================
// ������
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
#ifdef USE_SOUND
	HRESULT hr;

	// COM���C�u�����̏�����
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, _T("XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I"), _T("�x���I"), MB_ICONWARNING);

		// COM���C�u�����̏I������
		//CoUninitialize();

		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, _T("�}�X�^�[�{�C�X�̐����Ɏ��s�I"), _T("�x���I"), MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		//CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFileW(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, _T("�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)"), _T("�x���I"), MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, _T("�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)"), _T("�x���I"), MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)"), _T("�x���I"), MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)"), _T("�x���I"), MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, _T("WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)"), _T("�x���I"), MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)"), _T("�x���I"), MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)"), _T("�x���I"), MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)"), _T("�x���I"), MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)"), _T("�x���I"), MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �\�[�X�{�C�X�̐���
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("�\�[�X�{�C�X�̐����Ɏ��s�I"), _T("�x���I"), MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = g_aParam[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}
	if (g_pMasteringVoice) {
		g_pMasteringVoice->SetVolume(SOUNDSTARTPERCENT);
	}
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		g_apSourceVoice[i]->SetVolume(SOUNDSTARTPERCENT);
	}
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSound(void)
{
#ifdef USE_SOUND
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	//CoUninitialize();
#endif
}

//=============================================================================
// �Z�O�����g�Đ�(��~)
//=============================================================================
HRESULT PlaySound(SOUND_LABEL label)
{
#ifdef USE_SOUND
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = g_aParam[label].nCntLoop;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	//���̂��
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[label]->Start(0);

	//if (!xa2state.BuffersQueued != 0)
	//{// �Đ���
	//	//// �ꎞ��~
	//	//g_apSourceVoice[label]->Stop(0);

	//	//// �I�[�f�B�I�o�b�t�@�̍폜
	//	//g_apSourceVoice[label]->FlushSourceBuffers();

	//	// �I�[�f�B�I�o�b�t�@�̓o�^
	//	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	//	// �Đ�
	//	g_apSourceVoice[label]->Start(0);
	//}
#endif

	return S_OK;
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void StopSound(SOUND_LABEL label)
{
#ifdef USE_SOUND
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
#endif
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void StopSound(void)
{
#ifdef USE_SOUND
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
#endif
}

//=============================================================================
// �Z�O�����g�ꎞ��~
//=============================================================================
void PauseSound( void )
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; ++nCntSound) {
		if (g_apSourceVoice[nCntSound]) {
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop();
		}
	}
}

//=============================================================================
// �Z�O�����g�ĊJ
//=============================================================================
void ResumeSound( void )
{
	// �ĊJ
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (g_apSourceVoice[nCntSound]) {
			// �ĊJ
			g_apSourceVoice[nCntSound]->Start();
		}
	}
}

void ResumeSoundOne(int no)
{
	if (g_apSourceVoice[no]) {
		// �ĊJ
		g_apSourceVoice[no]->Start();
	}
}

//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

// ���ʐݒ�
void SetVolume(float fVol)
{
	if (GetMouseButton(MOUSEBUTTON_L)) {
		SoundSet[0] = fVol;
		if (g_pMasteringVoice) {
			g_pMasteringVoice->SetVolume(SoundSet[0]);
		}
	}
}

void SetVolumeOne(float fVol)
{
	if (GetMouseRelease(MOUSEBUTTON_L) || true) {
		SoundSet[0] += fVol;
		if (SoundSet[0] > SOUNDMAXPERCENT)SoundSet[0] = SOUNDMAXPERCENT;
		if (SoundSet[0] < 0.0f)SoundSet[0] = 0.0f;
		if (g_pMasteringVoice) {
			g_pMasteringVoice->SetVolume(SoundSet[0]);
		}
	}
}

// ���ʐݒ�
void SetSourceVolumeAll(float fVol,int Sno)
{
	if (GetMouseButton(MOUSEBUTTON_L) || true) {
		SoundSet[Sno] = fVol;
		switch (Sno)
		{
		case(1):
			for (int i = SOUND_LABEL_BGM001; i <= SOUND_LABEL_BGMMAX; i++)
			{
				g_apSourceVoice[i]->SetVolume(SoundSet[1]);
			}
			break;
		case(2):
			for (int i = SOUND_LABEL_SE_01; i <= SOUND_LABEL_SE_MAX; i++)
			{
				g_apSourceVoice[i]->SetVolume(SoundSet[2]);
			}
			break;
		case(3):
			for (int i = SOUND_LABEL_VOICE001; i <= SOUND_LABEL_VOICEMAX; i++)
			{
				g_apSourceVoice[i]->SetVolume(SoundSet[3]);
			}
			break;
		default:
			break;
		}
	}
}

// ���ʐݒ�
void SetSourceVolume(float fVol, int no)
{
	if (GetMouseRelease(MOUSEBUTTON_L)) {
		SoundSet[no] += fVol;
		if (SoundSet[no] < 0.0f)SoundSet[no] = 0.0f;
		if (SoundSet[no] > SOUNDMAXPERCENT)SoundSet[no] = SOUNDMAXPERCENT;
		switch (no)
		{
		case(1):
			for (int i = SOUND_LABEL_BGM001; i <= SOUND_LABEL_BGMMAX; i++)
			{
				g_apSourceVoice[i]->SetVolume(SoundSet[1]);
			}
			break;
		case(2):
			for (int i = SOUND_LABEL_SE_01; i <= SOUND_LABEL_SE_MAX; i++)
			{
				g_apSourceVoice[i]->SetVolume(SoundSet[2]);
			}
			break;
		case(3):
			for (int i = SOUND_LABEL_VOICE001; i <= SOUND_LABEL_VOICEMAX; i++)
			{
				g_apSourceVoice[i]->SetVolume(SoundSet[3]);
			}
			break;
		default:
			break;
		}
	}
}

//int SoundMouseMenuCollision()
//{
//	int MMBNo = -1;
//	for (int i = 0; i < 12; i++)
//	{
//
//		if ((int)Soundbuttonplace[i].w > (int)GetWindowMousePosX() && (int)Soundbuttonplace[i].x < (int)GetWindowMousePosX())
//		{
//
//			if ((int)Soundbuttonplace[i].y > (int)GetWindowMousePosY() && (int)Soundbuttonplace[i].z < (int)GetWindowMousePosY())
//			{
//				MMBNo = i;
//				break;
//			}
//		}
//	}
//	return MMBNo;
//}

//float GetSMVolume(int no)
//{
//	int Percent = (int)GetWindowMousePosX();
//	if (Percent > (int)Soundbuttonplace[no].w)Percent = (int)Soundbuttonplace[no].w;
//	if (Percent < (int)Soundbuttonplace[no].x)Percent = (int)Soundbuttonplace[no].x;
//	return (float)(Percent - Soundbuttonplace[no].x)*SOUNDMAXPERCENT / (Soundbuttonplace[no].w - Soundbuttonplace[no].x);
//}

float GetSoundVolume(int a)
{
	return SoundSet[a] / SOUNDMAXPERCENT;
}

void ResetSound()
{
	SetVolume(SOUNDSTARTPERCENT);
	for (int i = 1; i < 4; i++)
	{
		SetSourceVolumeAll(SOUNDSTARTPERCENT,i);
	}
}

float GetSoundLevel(int no)
{
	return SoundSet[no];
}