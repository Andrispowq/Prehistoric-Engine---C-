#ifndef FRAMEWORKCONFIG_H
#define FRAMEWORKCONFIG_H

#include <fstream>

#include "engine/prehistoric/core/util/Util.h"
#include "engine/prehistoric/core/math/Math.h"
#include "engine/prehistoric/core/log/Log.h"

/*
	Implemented:
		-
	Under development:
		OpenGL, Vulkan
	Planned:
		Vulkan_RTX, DirectX_11, DirectX_12, DirectX_RTX
*/
enum API
{
	OpenGL, Vulkan, Vulkan_RTX, DirectX_11, DirectX_12, DirectX_RTX, NO_API
};

namespace FrameworkConfig
{
	void LoadConfig(const std::string& path);

	extern std::string windowName;
	extern uint32_t windowWidth;
	extern uint32_t windowHeight;
	extern bool windowFullScreen;
	extern bool windowResizable;
	extern bool windowVSync;
	extern uint32_t windowNumSamples;
	extern uint32_t windowMaxFPS;

	extern API api;
	extern Vector2i apiVersion;
	extern bool apiVulkanUseValidationLayers;
};

#endif