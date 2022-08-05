#pragma once
#include <unordered_map>
#include <vector>
#include <SDL2/SDL.h>
#include "Shader.h"
#include "../Math/mat4.h"

class Game;
class Mesh;
class MeshElement;
class Texture;

class Renderer {
public:

	Renderer(Game*, int ScreenWidth, int ScreenHeight);

	~Renderer();

	void AddMeshElement(MeshElement*);

	Mesh* GetMesh(const std::string& meshName);

	Texture* GetTexture(const std::string& textName);

	void Draw();

	void SetViewMatrix(const mat4& newViewMat) { viewMat = newViewMat; }

private:
	void DrawScene();

	Game* game = nullptr;
	SDL_Window* sdlWindow = nullptr;
	SDL_GLContext sdlContext;

	std::unordered_map<std::string, Mesh*> meshes;
	std::unordered_map<std::string, Texture*> textures;

	std::vector<MeshElement*> meshElements;

	Shader shader;

	mat4 viewMat;
	mat4 projMat;

};