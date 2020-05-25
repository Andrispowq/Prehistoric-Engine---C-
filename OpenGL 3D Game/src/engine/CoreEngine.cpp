#include "engine/prehistoric/core/util/Includes.hpp"
#include "CoreEngine.h"

const static double NANOSECOND = std::pow(10, 9);

CoreEngine::CoreEngine()
{
	running = false;
	engine = new Engine();

	frameTime = 1.0 / FrameworkConfig::windowMaxFPS;
}

CoreEngine::~CoreEngine()
{
	delete engine;
}

void CoreEngine::Start()
{
	if (running)
		return;

	running = true;
	Run();
}

void CoreEngine::Stop()
{
	if (!running)
		return;

	running = false;
}

/*void CoreEngine::Run()
{
	long lastTime = Time::getTimeNanoseconds();
	double amountOfTicks = 60.0;
	double ns = pow(10, 9) / amountOfTicks;
	double delta = 0;
	long timer = Time::getTimeNanoseconds() / pow(10, 6);
	uint32_t updates = 0;
	uint32_t frames = 0;

	while (running)
	{
		long now = Time::getTimeNanoseconds();
		bool render = false;

		delta += (now - lastTime) / ns;
		lastTime = now;

		while (delta >= 1) 
		{
			if (engine->GetRenderingEngine()->GetWindow()->ShouldClose())
			{
				Stop();
				break;
			}

			Input(delta);
			Update();

			updates++;
			delta--;
		}

		Render();
		frames++;

		if ((Time::getTimeNanoseconds() / pow(10, 6) - timer) > 1000)
		{
			timer += 1000;
			PR_LOG_MESSAGE("FPS: %i, TICKS: %i\n", frames, updates);
			frames = 0;
			updates = 0;
		}
	}
}*/

void CoreEngine::Run()
{
	uint32_t frames = 0;
	double frameCounter = 0;

	long long lastTime = Time::getTimeNanoseconds();
	double unprocessedTime = 0;

	while (running)
	{
		bool render = false;

		long long startTime = Time::getTimeNanoseconds();
		long long passedTime = startTime - lastTime;
		lastTime = startTime;

		unprocessedTime += passedTime / NANOSECOND;
		frameCounter += passedTime;

		while (unprocessedTime > frameTime)
		{
			render = true;
			unprocessedTime -= frameTime;

			if (engine->GetRenderingEngine()->GetWindow()->ShouldClose())
			{
				Stop();
				break;
			}

			Input(std::max(passedTime / NANOSECOND, frameTime));
			Update();

			if (frameCounter >= NANOSECOND)
			{
				PR_LOG(CYAN, "FPS: %i\n", frames);
				PR_LOG(CYAN, "FPS: %f\n", NANOSECOND / (passedTime));
				frames = 0;
				frameCounter = 0;
			}
		}

		if (render)
		{
			Render();
			frames++;
		}
		else
		{
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(0ms);
		}
	}
}