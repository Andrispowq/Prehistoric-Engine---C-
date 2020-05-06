#ifndef VK_PIPELINE_H
#define VK_PIPELINE_H

#include "engine/prehistoric/common/rendering/pipeline/Pipeline.h"

#include <vulkan/vulkan.h>

#include "engine/platform/vulkan/framework/surface/VKSurface.h"
#include "engine/platform/vulkan/framework/device/VKDevice.h"
#include "engine/platform/vulkan/framework/swapchain/VKSwapchain.h"
#include "engine/platform/vulkan/buffer/VKMeshVBO.h"

class VKPipeline : public Pipeline
{
public:
	VKPipeline(Shader* shader);
	virtual ~VKPipeline();

	virtual void CreatePipeline(Window* window) override;

	virtual void BindPipeline() const override;
	virtual void RenderPipeline() const override;
	virtual void UnbindPipeline() const override;

	virtual void DestroyPipeline() override;

	virtual void RecreatePipeline();
protected:
	//External
	VKSurface* surface;
	VKPhysicalDevice* physicalDevice;
	VKDevice* device;

	Window* window;
	VKSwapchain* swapchain;

	//Local
	bool exists;
};

#endif