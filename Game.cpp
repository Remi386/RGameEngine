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
#include "Render/Mesh.h"

Game::Game(std::string_view iniFile /* = game.ini*/)
	:timer(Timer::FrameRate::FPS30)
{
	loadIni(iniFile);
	int ScreenWidth = 800;
	int ScreenHeight = 600;
	try {
		int ScreenWidth = std::stoi((*settings.find("ScreenWidth")).second);
		int ScreenHeight = std::stoi((*settings.find("ScreenHeight")).second);
	}
	catch (std::exception& ex) {
		Debug::Out(rIMPORTANT) << "Error while processing size of screen: " 
						       << ex.what() << std::endl;
	}

	renderer = new Renderer(this, ScreenWidth, ScreenHeight);

	auto cubeActor = new TempActor(this);
	MeshElement* mesh = new MeshElement(cubeActor);
	mesh->SetMesh(renderer->GetMesh("Cube.rmesh"));

	cubeActor->AddElement(mesh);
	cubeActor->SetPosition(vec3(0.0f, 2.36f, 5.0f));
	cubeActor->SetScale(3.0f);

	quat rotation(vec3::UnitY, Math::ToRadians(45.0));
	rotation *= quat(vec3::UnitX, -Math::ToRadians(30.0));
	cubeActor->SetRotation(rotation);

	auto camera = new Camera(this);
	camera->SetPosition(vec3(0.0, 2.0, 0.0));

	float wallSize = 20.0;

	auto CreateWall = [this, wallSize](const std::string& meshName) {
		TempActor* wall = new TempActor(this);
		wall->SetScale(wallSize / 2);
		MeshElement* mesh = new MeshElement(wall);
		mesh->SetMesh(this->GetRenderer()->GetMesh(meshName));
		return wall;
	};

	// forward and back walls
	for (int i = -2; i < 2; ++i) {
		for (int j = -2; j <= 2; j += 4) {
			auto wall = CreateWall("Wall.rmesh");
			wall->SetPosition(vec3(wallSize * i + wallSize / 2, 10.0, wallSize * j));
		}
	}

	quat WallRotation = quat(vec3::UnitY, Math::ToRadians(90.0f));

	// left and right walls
	for (int i = -2; i <= 2; i += 4) {
		for (int j = -2; j < 2; j++) {
			auto wall = CreateWall("Wall.rmesh");
			wall->SetPosition(vec3(wallSize * i, 10.0, wallSize * j + wallSize / 2));
			wall->SetRotation(WallRotation);
		}
	}

	WallRotation = quat(vec3::UnitX, Math::ToRadians(90.0f));

	// Floor
	for (int i = -2; i < 2; ++i) {
		for (int j = -2; j < 2; j++) {
			auto wall = CreateWall("Floor.rmesh");
			wall->SetPosition(vec3(wallSize * i + wallSize / 2,
								   0.0, wallSize * j + wallSize / 2));

			wall->SetRotation(WallRotation);
		}
	}

}

Game::~Game()
{
	delete renderer;
}

void Game::Loop()
{
	while (isRunning) 
	{
		timer.UpdateTimer();
		float deltaTime = timer.GetFrameDifference();

		ProcessInput();

		for (auto actor : actors) {
			actor->Update(deltaTime);
		}

		renderer->Draw();

		while (!timer.IsFrameEnd())
		{}
	}
}

void Game::ProcessInput()
{

	inputSystem.PreUpdate();

	SDL_Event even;
	while (SDL_PollEvent(&even)) {

		switch (even.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEWHEEL:
			inputSystem.ProcessEvent(even);
		case SDL_WINDOWEVENT:
			if(even.window.event == SDL_WINDOWEVENT_RESIZED)
				renderer->OnWindowResize(even.window.data1, even.window.data2);
			
		default:
			break;
		}
	}
	inputSystem.Update();

	InputState& inputState = inputSystem.GetInputState();

	for (auto actor : actors) {
		actor->ProcessInput(inputState);
	}
}

void Game::AddGameActor(GameActor* actor)
{
	actors.push_back(actor);
}

void Game::RemoveGameActor(GameActor* actor)
{
	actors.erase(std::remove(actors.begin(), actors.end(), actor), actors.end());
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

	auto verboseLevel = settings.find("VerboseLevel");
	if (verboseLevel == settings.end())
	{
		settings.emplace("VerboseLevel", "5");
	}
	else {
		int verbLevel = 5;

		try {
			verbLevel = std::stoi(verboseLevel->second);
		} catch (const std::exception& e) {
			Debug::Out(rIMPORTANT) << "Unable to cast verbose level to int: " << e.what() << std::endl;
		}

		if (verbLevel > int(DebugLVL::rSPAM) || verbLevel < int(DebugLVL::rCRITICAL))
		{
			Debug::Out(rIMPORTANT) << "Verbose level value should be between " 
				<< int(rCRITICAL) << " and " << int(rSPAM) << std::endl;
			verbLevel = int(rSPAM);
		}

		Debug::setDebugLevel(DebugLVL(verbLevel));

	}

	settings.emplace("ResourceFolders", "");

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