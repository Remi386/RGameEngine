#pragma once
#include <unordered_map>
#include <vector>
#include <SDL2/SDL.h>
#include "Shader.h"

class Game;
class Mesh;
class MeshElement;

class Renderer {
public:

	Renderer(Game*, int ScreenWidth, int ScreenHeight);

	~Renderer();

	void AddMeshElement(MeshElement*);

	Mesh* GetMesh(const std::string& meshName);

	void Draw();

private:
	void DrawScene();

	Game* game;
	SDL_Window* sdlWindow;
	SDL_GLContext sdlContext;

	std::unordered_map<std::string, Mesh*> meshes;

	std::vector<MeshElement*> meshElements;

	Shader commonShader;

};