#include<memory>

class Audio
{
public:
	Audio();
	~Audio();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};