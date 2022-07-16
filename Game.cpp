#include "Game.h"
#include <fstream>
#include <sstream>
#include "SDL2/SDL.h"
#include "Objects/GameActor.h"
#include "DebugLib/DebugOut.h"
#include "Objects/TempActor.h"
#include "Render/MeshElement.h"
#include "Render/Renderer.h"

Game::Game(std::string_view iniFile /* = game.ini*/)
{
	loadIni(iniFile);
	
	renderer = new Renderer(this, ScreenWidth, ScreenHeight);

	auto tmpActor = new TempActor(this);
	MeshElement* mesh = new MeshElement(tmpActor);
	mesh->SetMesh(renderer->GetMesh("square.obj"));

	tmpActor->AddElement(mesh);

	actors.push_back(tmpActor);
	
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

		SDL_Event even;

		while (SDL_PollEvent(&even)) {
			if (even.type == SDL_QUIT) {
				running = false;
			}
		}

		for (auto actor : actors) {
			actor->Update();
		}

		renderer->Draw();
	}

}
// Needs to be replaced by associative containers
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

		std::stringstream sStream(std::move(line));
		sStream >> propert;

		float value = 0;
		char equalChar;
		if(propert[0] != '[' && propert[0] != ' ')
			sStream >> equalChar >> value;

		if (propert == "ScreenWidth") {
			ScreenWidth = int(value);
		}
		
		if (propert == "ScreenHeight") {
			ScreenHeight = int(value);
		}

		if (propert == "VerboseLevel") {
			if (int(value) < int(rCRITICAL) || int(value) > int(rSPAM)) {
				Debug::Out(rCOMMON) << "VerboseLevel value should be between" << int(rCRITICAL)
									<< " and " << int(rSPAM) << std::endl;
			}
			else {
				Debug::setDebugLevel(DebugLVL(value));
			}
		}

	}

	return true;
}