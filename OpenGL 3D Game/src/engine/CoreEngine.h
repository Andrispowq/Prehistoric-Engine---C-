#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#include "engine/config/FrameworkConfig.h"
#include "engine/prehistoric/core/Engine.h"
#include "engine/prehistoric/core/util/time/Time.h"

#include <chrono>
#include <thread>

class CoreEngine
{
public:
	CoreEngine();
	virtual ~CoreEngine();

	void Start();
private:
	void Stop();

	void Run();

	void Input(double passedTime) { engine->Input(static_cast<float>(passedTime)); }
	void Update() { engine->Update(); }
	void Render() { engine->Render(); }

	CoreEngine(const CoreEngine& engine) = delete;
	CoreEngine operator=(const CoreEngine& engine) = delete;
private:
	bool running;
	double frameTime;

	Engine* engine;
};

#endif