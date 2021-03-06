#include "engine/prehistoric/core/util/Includes.hpp"
#include "GLPrefilterShader.h"

#include "engine/config/EnvironmentMapConfig.h"

GLPrefilterShader::GLPrefilterShader()
{
	AddShader(ResourceLoader::LoadShaderGL("opengl/environmentMap/prefilter_VS.glsl"), VERTEX_SHADER);
	AddShader(ResourceLoader::LoadShaderGL("opengl/environmentMap/prefilter_FS.glsl"), FRAGMENT_SHADER);

	CompileShader();

	AddUniform("m_view");
	AddUniform("m_projection");

	AddUniform("environmentMap");
	AddUniform("roughness");
	AddUniform("resolution");
}

void GLPrefilterShader::UpdateUniforms(const Matrix4f& projection, const Matrix4f& view, Texture* texture, float roughness) const
{
	SetUniform("m_view", view);
	SetUniform("m_projection", projection);

	texture->Bind(0);
	SetUniformi("environmentMap", 0);

	SetUniformf("environmentMap", roughness);
	SetUniformf("resolution", (float)EnvironmentMapConfig::prefilterMapResolution);
}
