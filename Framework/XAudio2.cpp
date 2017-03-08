#pragma comment(lib, "xaudio2")
#include "XAudio2.h"

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#define ASSERT(hr) if(!SUCCEEDED(hr)){ throw hr; }

HRESULT XAudio2::FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;

		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT XAudio2::ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}

//void Audio::Test() {
//	WAVEFORMATEXTENSIBLE wfx = { 0 };
//	XAUDIO2_BUFFER buffer = { 0 };
//
//	HANDLE hFile = CreateFile(L"E:\\Touhou\\demo\\OOPLab_Sample\\game_sample\\music\\bgm_stg00.wav", GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
//
//	if (INVALID_HANDLE_VALUE == hFile) throw HRESULT_FROM_WIN32(GetLastError());
//	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN)) throw HRESULT_FROM_WIN32(GetLastError());
//
//	DWORD dwChunkSize;
//	DWORD dwChunkPosition;
//	FindChunk(hFile, 'FFIR', dwChunkSize, dwChunkPosition);
//	DWORD filetype;
//	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
//	if (filetype != 'EVAW') throw S_FALSE;
//
//	FindChunk(hFile, ' tmf', dwChunkSize, dwChunkPosition);
//	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
//
//	FindChunk(hFile, 'atad', dwChunkSize, dwChunkPosition);
//	BYTE * pDataBuffer = new BYTE[dwChunkSize];
//	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);
//
//	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
//	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
//	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
//
//
//	//***********************************************
//	//*                                             *
//	//***********************************************
//
//	IXAudio2SourceVoice* pSourceVoice;
//	HRESULT hr = _engine->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx);
//	ASSERT(hr);
//
//	hr = pSourceVoice->SubmitSourceBuffer(&buffer);
//	ASSERT(hr);
//
//	hr = pSourceVoice->Start(0);
//	ASSERT(hr);
//
//	pSourceVoice->SetVolume(0.05);
//}

XAudio2 * XAudio2::Instance()
{
	static XAudio2 instance;
	return &instance;
}

IXAudio2SourceVoice* XAudio2::LoadWave(char* sourcePath)
{
	WAVEFORMATEXTENSIBLE wfx = { 0 };
	XAUDIO2_BUFFER buffer = { 0 };

	int length = strlen(sourcePath) + 1;
	wchar_t* wPath = new wchar_t[length];
	mbstowcs_s(0, wPath, length, sourcePath, _TRUNCATE);
	HANDLE hFile = CreateFile(wPath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);

	if (INVALID_HANDLE_VALUE == hFile) throw HRESULT_FROM_WIN32(GetLastError());
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN)) throw HRESULT_FROM_WIN32(GetLastError());

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE) throw S_FALSE;

	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

	IXAudio2SourceVoice* sourceVoice;
	HRESULT hr = _engine->CreateSourceVoice(&sourceVoice, (WAVEFORMATEX*)&wfx);
	ASSERT(hr);

	hr = sourceVoice->SubmitSourceBuffer(&buffer);
	ASSERT(hr);

	return sourceVoice;
}

XAudio2::XAudio2() :_engine(nullptr), _voice(nullptr) {
	HRESULT hr = XAudio2Create(&_engine);
	ASSERT(hr);

	hr = _engine->CreateMasteringVoice(&(_voice));
	ASSERT(hr);

	//IXAudio2SourceVoice* test;
	//_engine->CreateSourceVoice(&test, _waveFormat);
	//test->SubmitSourceBuffer(_buffer);
	//test->Start();
}

XAudio2 :: ~XAudio2() {
	_engine->Release();
	//CoUninitialize();
}