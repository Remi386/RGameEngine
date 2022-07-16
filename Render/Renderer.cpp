#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "Renderer.h"
#include "../Game.h"
#include "../DebugLib/DebugOut.h"
#include "Mesh.h"
#include "MeshElement.h"

Renderer::~Renderer()
{
	if (sdlWindow)
		delete sdlWindow;
}

Renderer::Renderer(Game* game_, int ScreenWidth_, int ScreenHeight_)
{
	game = game_;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		Debug::Out(rCRITICAL) << "Cannot initialaze SDL: " << SDL_GetError() << std::endl;
		std::exit(100);
	}

	// Set OpenGL attributes
	// Use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	sdlWindow = SDL_CreateWindow("Title", 50, 50, 
		ScreenWidth_, ScreenHeight_, SDL_WINDOW_OPENGL);

	if (!sdlWindow)
	{
		Debug::Out(rCRITICAL) << "Failed to create window: " << SDL_GetError() << std::endl;
		std::exit(101);
	}

	sdlContext = SDL_GL_CreateContext(sdlWindow);

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		// Problem: glewInit failed, something is seriously wrong.
		Debug::Out(rCRITICAL) << "Cannot initialize GLEW " << glewGetErrorString(err) << std::endl;
		exit(102);
	}

	int glErr = glGetError();

	while (glErr != GL_NO_ERROR) {
		Debug::Out(rCRITICAL) << "glError: " << glErr << std::endl;
		glErr = glGetError();
	}

	if (!commonShader.Load("GLSL/CommonShader.vert", "GLSL/CommonShader.frag"))
	{
		Debug::Out(rCRITICAL) << "Cannot load shader files" << std::endl;
		std::exit(103);
	}

}

Mesh* Renderer::GetMesh(const std::string& meshName)
{
	Mesh* mesh = nullptr;
	if (meshes.contains(meshName))
		return meshes[meshName];
	else {
		mesh = new Mesh(this);
		if (!mesh->LoadMesh(meshName)) {
			return nullptr;
		}
		meshes.emplace(meshName, mesh);
		return mesh;
	}
}

void Renderer::Draw()
{
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawScene();

	SDL_GL_SwapWindow(sdlWindow);
}

void Renderer::AddMeshElement(MeshElement* meshElem)
{
	meshElements.push_back(meshElem);
}

void Renderer::DrawScene()
{
	commonShader.SetActive();

	for (auto mesh : meshElements) {
		mesh->Draw(&commonShader);
	}

}