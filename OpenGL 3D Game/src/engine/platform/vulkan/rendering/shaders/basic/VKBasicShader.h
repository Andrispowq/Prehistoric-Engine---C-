#ifndef VK_BASIC_SHADER_H
#define VK_BASIC_SHADER_H

#include "engine/platform/vulkan/rendering/shaders/VkShader.h"

#include <vulkan/vulkan.h>

#include "engine/prehistoric/core/gameObject/GameObject.h"
#include "engine/prehistoric/core/model/material/Material.h"
#include "engine/prehistoric/component/light/Light.h"
#include "engine/prehistoric/component/renderer/Renderer.h"

class VKBasicShader : public VKShader
{
public:
	VKBasicShader(Window* window);
	virtual ~VKBasicShader() {}

	virtual void UpdateShaderUniforms(Camera* camera, std::vector<Light*> lights) const override;
	virtual void UpdateObjectUniforms(GameObject* object) const override;
};

#endif