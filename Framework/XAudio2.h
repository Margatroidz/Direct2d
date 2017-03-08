#include <xaudio2.h>

class XAudio2
{
public:
	XAudio2(const XAudio2&) = delete;
	XAudio2& operator=(const XAudio2&) = delete;
	static XAudio2* Instance();
	IXAudio2SourceVoice* LoadWave(char* sourcePath);
private:
	XAudio2();
	~XAudio2();
	IXAudio2* _engine;
	IXAudio2MasteringVoice* _voice;
	HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);
};