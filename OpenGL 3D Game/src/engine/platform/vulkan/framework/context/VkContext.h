#ifndef VK_CONTEXT_H
#define VK_CONTEXT_H

#include "engine/prehistoric/common/framework/context/Context.h"

#include "VKInstance.h"
#include "engine/platform/vulkan/framework/device/VKPhysicalDevice.h"
#include "engine/platform/vulkan/framework/device/VKDevice.h"
#include "engine/platform/vulkan/framework/surface/VKSurface.h"

class VKContext : public Context
{
public:
	bool InitContext(Window* window) override;
	bool DeleteContext(Window* window) override;

	VKInstance GetInstance() const { return instance; }

	void* GetPhysicalDevice() override { return &physicalDevice; }
	void* GetDevice() override { return &logicalDevice; }

	VKSurface GetSurface() const { return surface; }
private:
	VKInstance instance;

	VKPhysicalDevice physicalDevice;
	VKDevice logicalDevice;

	VKSurface surface;
};

#endif