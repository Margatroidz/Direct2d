#pragma once
#include <memory>

class Audio
{
public:
	Audio(const Audio&) = delete;
	Audio& operator=(const Audio&) = delete;
	Audio(char* sourcePath);
	~Audio();
	void Play();
	void Stop();
	void SetVolume(float volumn);
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};