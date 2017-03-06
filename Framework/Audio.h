#include <xaudio2.h>

class Audio
{
public:
	Audio();
	~Audio();
	void Test();
private:
	IXAudio2* _engine;
	IXAudio2MasteringVoice* _voice;
};