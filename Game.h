#pragma once
//#include "Render/Renderer.h"
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

	int ScreenWidth = 800;
	int ScreenHeight = 600;

	bool loadIni(std::string_view iniFile);
	std::vector<GameActor*> actors;
	Renderer* renderer;
	Timer timer;
};