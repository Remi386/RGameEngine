#pragma once
#include "utils/Timer.h"
#include <vector>
#include <string_view>
#include <unordered_map>

class GameActor;
class Renderer;
class InputSystem;

class Game {
public:
	using StringMultiMap = std::unordered_multimap<std::string, std::string>;

	Game(std::string_view iniFile = "game.ini");

	~Game();

	Renderer* GetRenderer() { return renderer; }

	const StringMultiMap& GetSettings() { return settings; }

	void Loop();

	void AddGameActor(GameActor* actor);

	void RemoveGameActor(GameActor* actor);

	/// <summary>
	/// Searching for file in resource folders, defined in ini file
	/// </summary>
	/// <param name="fileName"></param>
	/// <returns> string with absolute path, empty string if file doesnt exist</returns>
	std::string FindFile(const std::string& fileName);

private:
	bool loadIni(std::string_view iniFile);

	void ProcessInput();

	StringMultiMap settings;
	std::vector<GameActor*> actors;
	Renderer* renderer;
	InputSystem* inputSystem;
	Timer timer;
	bool isRunning = true;
};