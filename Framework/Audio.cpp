#include "Audio.h"
#include <xaudio2.h>

struct Audio::Impl
{
	//IXAudio2* _engine;
	//IXAudio2MasteringVoice* _voice;

	//const WAVEFORMATEX* _waveFormat;
	//const XAUDIO2_BUFFER* _buffer;
};

Audio :: Audio()
{
	//XAudio2Create(&(pimpl->_engine));
	//pimpl->_engine->CreateMasteringVoice(&(pimpl->_voice));

	//IXAudio2SourceVoice* test;
	//pimpl->_engine->CreateSourceVoice(&test, pimpl->_waveFormat);
	//test->SubmitSourceBuffer(pimpl->_buffer);
	//test->Start();
}

Audio :: ~Audio()
{
	//pimpl->_engine->Release();
	//CoUninitialize();
}