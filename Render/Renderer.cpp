#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_config_windows.h>
#include "Renderer.h"
#include "../Game.h"
#include "../DebugLib/DebugOut.h"
#include "Mesh.h"
#include "MeshElement.h"

Renderer::~Renderer()
{
	if (sdlWindow)
		SDL_DestroyWindow(sdlWindow);
}

Renderer::Renderer(Game* game_, int ScreenWidth_, int ScreenHeight_)
	:game(game_)
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		Debug::Out(rCRITICAL) << "Cannot initialaze SDL: " << SDL_GetError() << std::endl;
		std::exit(100);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	
	// double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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

	viewMat = mat4::CreateLookAt(vec3::Zero, vec3::UnitZ, vec3::UnitY);

	projMat = mat4::CreatePerspective(Math::ToRadians(80.0f), float(ScreenWidth_),
									  float(ScreenHeight_), 1.0f, 1000.f);

	commonShader.SetActive();
	commonShader.SetUniformMatrix4("view", viewMat);
	commonShader.SetUniformMatrix4("proj", projMat);
	
	Debug::Out(rSPAM) << "viewProjection matrix seted up" << std::endl;
}

Mesh* Renderer::GetMesh(const std::string& meshName)
{
	Mesh* mesh = nullptr;
	if (meshes.contains(meshName))
		return meshes[meshName];
	else {
		mesh = new Mesh(this);
		if (!mesh->LoadMesh(meshName)) {
			Debug::Out(rCRITICAL) << "Unable to load mesh: " << meshName << std::endl;
			std::exit(104);
		}
		meshes.emplace(meshName, mesh);
		return mesh;
	}
}

void Renderer::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	commonShader.SetActive();
	commonShader.SetUniformMatrix4("view", viewMat);
	commonShader.SetUniformMatrix4("proj", projMat);

	DrawScene();

	SDL_GL_SwapWindow(sdlWindow);
}

void Renderer::AddMeshElement(MeshElement* meshElem)
{
	meshElements.push_back(meshElem);
}

void Renderer::DrawScene()
{

	for (auto mesh : meshElements) {
		mesh->Draw(&commonShader);
	}

}

