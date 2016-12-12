#include<memory>

class Audio
{
public:
	Audio();
	~Audio();
private:
	struct impl;
	std::unique_ptr<impl> pimpl;
};