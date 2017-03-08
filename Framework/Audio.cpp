#include "Audio.h"
#include "XAudio2.h"

struct Audio::Impl {
	IXAudio2SourceVoice* _sourceVoice;
};

Audio::Audio(char* sourcePath) :pimpl(new Impl) {
	pimpl->_sourceVoice = XAudio2::Instance()->LoadWave(sourcePath);
}

Audio::~Audio() {}

void Audio::Play() {
	pimpl->_sourceVoice->Start();
}

void Audio::Stop() {
	pimpl->_sourceVoice->Stop();
}

void Audio::SetVolume(float volumn)
{
	pimpl->_sourceVoice->SetVolume(volumn);
}

