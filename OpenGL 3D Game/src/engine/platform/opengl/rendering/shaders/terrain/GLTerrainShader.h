#ifndef GL_TERRAIN_SHADER_H
#define GL_TERRAIN_SHADER_H

#include <glew.h>

#include "engine/platform/opengl/rendering/shaders/GLShader.h"

class GLTerrainShader : public GLShader
{
public:
	GLTerrainShader();
	virtual ~GLTerrainShader() {}

	virtual void UpdateShaderUniforms(Camera* camera, std::vector<Light*> lights) const override;
	virtual void UpdateObjectUniforms(GameObject* object) const override;
};

#endif