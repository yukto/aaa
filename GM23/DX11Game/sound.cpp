//=============================================================================
//
// サウンド処理 [sound.cpp]
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
// パラメータ構造体定義
//*****************************************************************************
typedef struct
{
	LPCWSTR	pFilename;		// ファイル名
	BYTE	nCntLoop;		// ループカウント
} SOUNDPARAM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
#ifdef USE_SOUND
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// マスターボイス
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
static float SoundSet[4];	//0が全体でそれ以外がBGM,SE,VOICEになっている
static XMFLOAT4 Soundbuttonplace[12];
static int Mno;
#endif

// 各音素材のパラメータ
SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	{L"data/sound/bgm/bgm0.wav", -1}, // BGM0( -1はループ再生,0は一回だけ再生)
	{L"data/sound/bgm/bgm1.wav", -1}, 
	{L"data/sound/bgm/bgm2.wav", -1}, 
	{L"data/sound/bgm/bgm3.wav", -1}, 
	{L"data/sound/bgm/bgm4.wav", -1}, 
	{L"data/sound/bgm/bgm5.wav", -1}, // BGMMAX(固定)
	{L"data/sound/se/decide13.wav", 0 },
	{L"data/sound/se/kougekikaihi-02.wav", 0 },
	{L"data/sound/se/ショップ売買成立音.wav", 0 },
	{L"data/sound/se/se1.wav", 0 },
	{L"data/sound/se/se2.wav", 0 },
	{L"data/sound/se/se3.wav", 0 },// SEMMAX(固定)
	{L"data/sound/voice/voice1_01.wav", 0 },
	{L"data/sound/voice/voice1_02.wav", 0 },
	{L"data/sound/voice/voice1_03.wav", 0 },
	{L"data/sound/voice/voice1_04.wav", 0 },
	{L"data/sound/voice/voice1_05.wav", 0 },
	{L"data/sound/voice/voice1_06.wav", 0 },
	{L"data/sound/voice/voice1_07.wav", 0 },// VOICEMMAX(固定)
};

//=============================================================================
// 初期化
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
#ifdef USE_SOUND
	HRESULT hr;

	// COMライブラリの初期化
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, _T("XAudio2オブジェクトの作成に失敗！"), _T("警告！"), MB_ICONWARNING);

		// COMライブラリの終了処理
		//CoUninitialize();

		return E_FAIL;
	}
	
	// マスターボイスの生成
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, _T("マスターボイスの生成に失敗！"), _T("警告！"), MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		//CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFileW(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, _T("サウンドデータファイルの生成に失敗！(1)"), _T("警告！"), MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, _T("サウンドデータファイルの生成に失敗！(2)"), _T("警告！"), MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("WAVEファイルのチェックに失敗！(1)"), _T("警告！"), MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("WAVEファイルのチェックに失敗！(2)"), _T("警告！"), MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, _T("WAVEファイルのチェックに失敗！(3)"), _T("警告！"), MB_ICONWARNING);
			return S_FALSE;
		}
	
		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("フォーマットチェックに失敗！(1)"), _T("警告！"), MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("フォーマットチェックに失敗！(2)"), _T("警告！"), MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("オーディオデータ読み込みに失敗！(1)"), _T("警告！"), MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("オーディオデータ読み込みに失敗！(2)"), _T("警告！"), MB_ICONWARNING);
			return S_FALSE;
		}
	
		// ソースボイスの生成
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, _T("ソースボイスの生成に失敗！"), _T("警告！"), MB_ICONWARNING);
			return S_FALSE;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = g_aParam[nCntSound].nCntLoop;

		// オーディオバッファの登録
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
// 終了処理
//=============================================================================
void UninitSound(void)
{
#ifdef USE_SOUND
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// ソースボイスの破棄
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// オーディオデータの開放
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// マスターボイスの破棄
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	//CoUninitialize();
#endif
}

//=============================================================================
// セグメント再生(停止)
//=============================================================================
HRESULT PlaySound(SOUND_LABEL label)
{
#ifdef USE_SOUND
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = g_aParam[label].nCntLoop;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	//元のやつ
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	g_apSourceVoice[label]->Start(0);

	//if (!xa2state.BuffersQueued != 0)
	//{// 再生中
	//	//// 一時停止
	//	//g_apSourceVoice[label]->Stop(0);

	//	//// オーディオバッファの削除
	//	//g_apSourceVoice[label]->FlushSourceBuffers();

	//	// オーディオバッファの登録
	//	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	//	// 再生
	//	g_apSourceVoice[label]->Start(0);
	//}
#endif

	return S_OK;
}

//=============================================================================
// セグメント停止
//=============================================================================
void StopSound(SOUND_LABEL label)
{
#ifdef USE_SOUND
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
#endif
}

//=============================================================================
// セグメント停止
//=============================================================================
void StopSound(void)
{
#ifdef USE_SOUND
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
#endif
}

//=============================================================================
// セグメント一時停止
//=============================================================================
void PauseSound( void )
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; ++nCntSound) {
		if (g_apSourceVoice[nCntSound]) {
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop();
		}
	}
}

//=============================================================================
// セグメント再開
//=============================================================================
void ResumeSound( void )
{
	// 再開
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (g_apSourceVoice[nCntSound]) {
			// 再開
			g_apSourceVoice[nCntSound]->Start();
		}
	}
}

void ResumeSoundOne(int no)
{
	if (g_apSourceVoice[no]) {
		// 再開
		g_apSourceVoice[no]->Start();
	}
}

//=============================================================================
// チャンクのチェック
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
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
// チャンクデータの読み込み
//=============================================================================
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

// 音量設定
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

// 音量設定
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

// 音量設定
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