#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_config_windows.h>
#include "Renderer.h"
#include "../Game.h"
#include "../DebugLib/DebugOut.h"
#include "Mesh.h"
#include "MeshElement.h"
#include "Texture.h"

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
	
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	sdlWindow = SDL_CreateWindow("Title", 50, 50, ScreenWidth_, 
								 ScreenHeight_, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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
		Debug::Out(rCRITICAL) << "Cannot initialize GLEW " 
							  << glewGetErrorString(err) << std::endl;
		exit(102);
	}

	int glErr = glGetError();

	while (glErr != GL_NO_ERROR) {
		Debug::Out(rIMPORTANT) << "glError: " << glErr << std::endl;
		glErr = glGetError();
	}

	if (!shader.Load("GLSL/PhongShader.vert", "GLSL/PhongShader.frag"))
	{
		Debug::Out(rCRITICAL) << "Cannot load shader files" << std::endl;
		std::exit(103);
	}

	viewMat = mat4::CreateLookAt(vec3::Zero, vec3::UnitZ, vec3::UnitY);

	projMat = mat4::CreatePerspective(Math::ToRadians(90.0f), float(ScreenWidth_),
									  float(ScreenHeight_), 0.1f, 10000.f);

	shader.SetActive();
	
	shader.SetUniformFloat("specularPower", 70.0f);
	shader.SetUniformVector3("ambientLight", vec3(0.3f, 0.3f, 0.3f));

	shader.SetUniformVector3("dirLight.lightDirection", vec3(-1.0f, -0.577f, 0.f));
	shader.SetUniformVector3("dirLight.diffuseColor", vec3(0.8f, 0.9f, 1.0f));
	shader.SetUniformVector3("dirLight.specularColor", vec3(0.7f, 0.7f, 0.7f));
	
	shader.SetUniformVector3("cameraPosition", vec3(0.f, 0.f, 0.f));
	
}

Mesh* Renderer::GetMesh(const std::string& meshName)
{
	Mesh* mesh = nullptr;
	if (meshes.contains(meshName))
		return meshes[meshName];
	else {

		std::string pathToMesh = game->FindFile(meshName);
		if (pathToMesh.empty()) {
			Debug::Out(rCRITICAL) << "Cannot find mesh file: " << meshName << std::endl;
			std::exit(110);
		}

		mesh = new Mesh(this);
		if (!mesh->LoadMesh(pathToMesh)) {
			Debug::Out(rCRITICAL) << "Unable to load mesh: " << meshName << std::endl;
			std::exit(104);
		}
		meshes.emplace(meshName, mesh);

		return mesh;
	}
}

Texture* Renderer::GetTexture(const std::string& textName)
{
	Texture* text = nullptr;
	if (textures.contains(textName))
		return textures[textName];
	else {

		std::string pathToTexture = game->FindFile(textName);
		if (pathToTexture.empty()) {
			Debug::Out(rCRITICAL) << "Cannot find texture file: " << textName << std::endl;
			std::exit(111);
		}

		text = new Texture();
		if (!text->Load(pathToTexture)) {
			Debug::Out(rCRITICAL) << "Unable to load texture: " << textName << std::endl;
			std::exit(105);
		}
		textures.emplace(textName, text);

		return text;
	}
}

void Renderer::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_CULL_FACE);

	shader.SetActive();

	vec3 cameraDirection = mat4::Inversed(viewMat).GetTranslation();
	shader.SetUniformVector3("cameraPosition", cameraDirection);
	shader.SetUniformMatrix4("viewProjection", viewMat * projMat);

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
		mesh->Draw(&shader);
	}

}

void Renderer::OnWindowResize(uint32_t newWidth, uint32_t newHeight)
{
	Debug::Out(rCOMMON) << "Window resized: width = " << newWidth 
						<< ", height = " << newHeight << std::endl;

	glViewport(0, 0, newWidth, newHeight);

	projMat = mat4::CreatePerspective(Math::ToRadians(90.0f), float(newWidth),
									  float(newHeight), 0.1f, 10000.f);
}