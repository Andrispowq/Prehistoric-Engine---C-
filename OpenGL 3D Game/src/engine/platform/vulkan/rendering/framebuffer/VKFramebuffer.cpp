#include "engine/prehistoric/core/util/Includes.hpp"
#include "VKFramebuffer.h"
#include "engine/platform/vulkan/rendering/renderpass/VKRenderpass.h"

VKFramebuffer::VKFramebuffer(VKRenderpass& renderpass, VkExtent2D& swapchainExtent, VkImageView& colourAttachment, VkImageView& depthAttachment, VkImageView& colourAttachmentResolve, VkDevice& device)
{
	this->renderpass = &renderpass;
	this->swapchainExtent = &swapchainExtent;
	this->device = &device;

	attachments = new VkImageView[3]
	{
		colourAttachment,
		depthAttachment,
		colourAttachmentResolve
	};

	VkFramebufferCreateInfo framebufferInfo = {};
	framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferInfo.renderPass = renderpass.GetRenderPass();
	framebufferInfo.attachmentCount = 3;
	framebufferInfo.pAttachments = attachments;
	framebufferInfo.width = swapchainExtent.width;
	framebufferInfo.height = swapchainExtent.height;
	framebufferInfo.layers = 1;

	if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffer) != VK_SUCCESS)
	{
		PR_LOG_RUNTIME_ERROR("Failed to create framebuffer!\n");
	}
}

VKFramebuffer::~VKFramebuffer()
{
	vkDestroyFramebuffer(*device, framebuffer, nullptr);
}