#pragma once
#include "utils/Timer.h"
#include <vector>
#include <string_view>

class GameActor;
class Renderer;

class Game {
public:
	Game(std::string_view iniFile = "game.ini");

	~Game();

	Renderer* GetRenderer() { return renderer; }

	void Loop();

private:
	bool loadIni(std::string_view iniFile);

	void ProcessInput();

	int ScreenWidth = 800;
	int ScreenHeight = 600;

	std::vector<GameActor*> actors;
	Renderer* renderer;
	Timer timer;
};