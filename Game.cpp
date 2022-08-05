#include "Game.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <SDL2/SDL.h>
#include "Objects/GameActor.h"
#include "DebugLib/DebugOut.h"
#include "Objects/TempActor.h"
#include "Render/MeshElement.h"
#include "Render/Renderer.h"
#include "Objects/Camera.h"

Game::Game(std::string_view iniFile /* = game.ini*/)
	:timer(Timer::FrameRate::FPS30)
{
	loadIni(iniFile);
	int ScreenWidth = std::stoi((*settings.find("ScreenWidth")).second);
	int ScreenHeight = std::stoi((*settings.find("ScreenHeight")).second);

	renderer = new Renderer(this, ScreenWidth, ScreenHeight);

	auto tmpActor = new TempActor(this);
	MeshElement* mesh = new MeshElement(tmpActor);
	mesh->SetMesh(renderer->GetMesh("cube.rmesh"));

	tmpActor->AddElement(mesh);
	tmpActor->SetPosition(vec3(0.0f, 0.0f, 5.0f));
	tmpActor->SetScale(3.0f);

	quat rotation(vec3(0.0, 1.0, 0.0), Math::ToRadians(45.0));
	rotation *= quat(vec3(1.0, 0.0, 0.0), -Math::ToRadians(30.0));
	tmpActor->SetRotation(rotation);

	auto camera = new Camera(this);

	actors.push_back(tmpActor);
	actors.push_back(camera);
}

Game::~Game()
{
	delete renderer;
}

void Game::Loop()
{
	bool running = true;

	while (running) 
	{
		timer.UpdateTimer();
		float deltaTime = timer.GetFrameDifference();
		SDL_Event even;

		while (SDL_PollEvent(&even)) {
			if (even.type == SDL_QUIT) {
				running = false;
			}
		}

		ProcessInput();

		for (auto actor : actors) {
			actor->Update(deltaTime);
		}

		renderer->Draw();

		while (timer.WaitForFrameEnd())
		{}
	}
}

void Game::ProcessInput()
{
	const uint8_t* keyState = SDL_GetKeyboardState(nullptr);

	for (auto actor : actors) {
		actor->ProcessInput(keyState);
	}
}

bool Game::loadIni(std::string_view iniFile)
{
	Debug::setDebugLevel(rSPAM);

	std::ifstream inFile(iniFile.data());

	if (!inFile.is_open()) {
		Debug::Out(rCRITICAL) << "Cannot open ini file: " << iniFile << std::endl;
		return false;
	}

	std::string propert;
	
	while (!inFile.eof()) {
		std::string line;
		std::getline(inFile, line);

		if (line.empty() || line[0] == '[' || line[0] == ' ')
			continue;

		std::stringstream sStream(std::move(line));
		sStream >> propert;

		char equalChar;
		sStream >> equalChar;
		while (!sStream.eof())
		{
			std::string value;
			sStream >> value;
			settings.emplace(propert, value);
		}

		auto width = settings.find("ScreenWidth");
		if (width == settings.end())
		{
			settings.emplace("ScreenWidth", "800");
		}
		
		auto height = settings.find("ScreenHeight");
		if (height == settings.end())
		{
			settings.emplace("ScreenHeight", "600");
		}

		settings.emplace("ResourceFolders", "");

	}

	return true;
}

std::string Game::FindFile(const std::string& fileName)
{
	namespace fs = std::filesystem;

	auto iter = std::find_if(settings.find("ResourceFolders"), settings.end(),
		[&fileName](const auto& pair)
		{
			fs::path path = (pair.second.empty() ? "" : pair.second + "/") + fileName;

			return fs::exists(path);
		});

	if (iter == settings.end())
		return std::string();

	return 
		fs::absolute(
			fs::path((iter->second.empty() ? "" : iter->second + "/") + fileName)
		).string();
}