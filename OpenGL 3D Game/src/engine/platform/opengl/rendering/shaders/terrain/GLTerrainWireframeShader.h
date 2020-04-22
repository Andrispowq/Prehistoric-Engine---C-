#ifndef GL_TERRAIN_WIREFRAME_SHADER_H
#define GL_TERRAIN_WIREFRAME_SHADER_H

#include <glew.h>

#include "engine/platform/opengl/rendering/shaders/GLShader.h"

class GLTerrainWireframeShader : public GLShader
{
public:
	GLTerrainWireframeShader();
	virtual ~GLTerrainWireframeShader() {}

	virtual void UpdateUniforms(GameObject* object, Camera* camera, std::vector<Light*> lights) const override;
};

#endif