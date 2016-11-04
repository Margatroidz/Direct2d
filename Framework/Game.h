#pragma once

class Game 
{
public:
	static Game* Instance();
	void Test();
private:
	Game();
	~Game();
};