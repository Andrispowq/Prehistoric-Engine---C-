#ifndef VK_RENDERPASS_H
#define VK_RENDERPASS_H

#include <vulkan/vulkan.h>

#include "engine/platform/vulkan/framework/device/VKDevice.h"
#include "engine/platform/vulkan/rendering/framebuffer/VKFramebuffer.h"
#include "engine/platform/vulkan/rendering/command/VKCommandBuffer.h"

class VKRenderpass
{
public:
	VKRenderpass(VKPhysicalDevice& physicalDevice, VkDevice& device, VkFormat& colourImageFormat);
	virtual ~VKRenderpass();

	void BeginRenderpass(VKCommandBuffer& commandBuffer, VkExtent2D& swapchainExtent, VKFramebuffer& framebuffer, Vector4f clearColour);
	void EndRenderpass(VKCommandBuffer& commandBuffer);

	VkRenderPass GetRenderPass() const { return renderpass; }
private:
	VkRenderPass renderpass;

	VkDevice* device;
	VkFormat* imageFormat;
};

#endif