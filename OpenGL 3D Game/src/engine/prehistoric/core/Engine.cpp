#include "engine/prehistoric/core/util/Includes.hpp"
#include "Engine.h"

Engine::Engine()
{
	frameTime = 0;

	//Config loading
	FrameworkConfig::LoadConfig("res/config/framework.cfg");
	EngineConfig::LoadConfig("res/config/engine.cfg");

	//Rootobject init
	root = new GameObject();

	//Engines' initialization
	renderingEngine = new RenderingEngine();
	InputInstance.Init(renderingEngine->GetWindow());
	renderingEngine->Init();

	TerrainConfig::LoadConfig("res/config/terrain.cfg", renderingEngine->GetWindow());
	Scene::CreateScene(root, renderingEngine->GetWindow(), renderingEngine->GetCamera());
}

Engine::~Engine()
{
	Scene::DeleteData();
	Input::DeleteInstance();
	delete renderingEngine;

	delete root;
}

void Engine::Input(float frameTime)
{
	this->frameTime = frameTime;

	InputInstance.Update();

	renderingEngine->Input();
}

//For consistency: Engine updates the root node, and then the engines do the work they need to
//Most components will register themselves into an engine's list of components, and then the engine can update them
void Engine::Update()
{
	root->PreUpdate(this);

	renderingEngine->Update(frameTime);
}

void Engine::Render()
{
	//We cannot detect keys in the render loop, because it runs differently then the update and input loop
	root->PreRender(renderingEngine);

	renderingEngine->Render(root);
}