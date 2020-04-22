#include "engine/prehistoric/core/util/Includes.hpp"
#include "TerrainConfig.h"

#include "engine/prehistoric/modules/terrain/TerrainQuadtree.h"

namespace TerrainConfig
{
	float TerrainConfig::scaleY;
	float TerrainConfig::scaleXZ;

	int TerrainConfig::tessellationFactor;
	float TerrainConfig::tessellationSlope;
	float TerrainConfig::tessellationShift;

	std::vector<int> TerrainConfig::lodRanges;
	std::vector<int> TerrainConfig::lodMorphingAreas;

	std::string TerrainConfig::heightmap;
	std::vector<Material*> TerrainConfig::materials;

	void TerrainConfig::LoadConfig(const std::string& path, Window* window)
	{
		std::ifstream file;
		file.open(path.c_str());

		std::string line;

		if (file.is_open())
		{
			while (file.good())
			{
				std::getline(file, line);
				std::vector<std::string> tokens = Util::Split(line, ' ');
				std::vector<std::string> nameTokens = Util::Split(tokens[0], '.');

				if (nameTokens[0] == "scale")
				{
					if (nameTokens[1] == "y")
					{
						scaleY = (float)std::atof(tokens[1].c_str());
					}
					if (nameTokens[1] == "xz")
					{
						scaleXZ = (float)std::atof(tokens[1].c_str());
					}
				}

				if (nameTokens[0] == "tessellation")
				{
					if (nameTokens[1] == "factor")
					{
						tessellationFactor = std::atoi(tokens[1].c_str());
					}
					if (nameTokens[1] == "slope")
					{
						tessellationSlope = (float) std::atof(tokens[1].c_str());
					}
					if (nameTokens[1] == "shift")
					{
						tessellationShift = (float) std::atof(tokens[1].c_str());
					}
				}

				if (nameTokens[0] == "lod")
				{
					if (nameTokens[1] == "ranges")
					{
						lodRanges.reserve(std::atoi(tokens[1].c_str()));
					}
					if (nameTokens[1] == "range")
					{
						int index = std::atoi(tokens[1].c_str());
						int range = std::atoi(tokens[2].c_str());
						lodRanges.push_back(range);
						lodMorphingAreas.push_back(range - UpdateMorphingArea(index + 1));
					}
				}
				
				//TODO: per terrain!
				if (nameTokens[0] == "heightmap")
				{
					heightmap = tokens[1];
				}

				if (nameTokens[0] == "materials")
				{
					if (nameTokens[1] == "add")
					{
						materials.push_back(new Material(window));
					}
					else
					{
						Material* material = materials[materials.size() - 1];

						if (nameTokens[2] == "texture")
						{
							material->AddTexture(tokens[1], TextureLoader::LoadTexture(tokens[2], window));
						}
						else if (nameTokens[2] == "vec4")
						{
							material->AddVector4f(tokens[1], new Vector4f((float) std::atof(tokens[2].c_str()), (float)std::atof(tokens[3].c_str())
														, (float)std::atof(tokens[4].c_str()), (float)std::atof(tokens[5].c_str())));
						}
						else if (nameTokens[2] == "vec3")
						{
							material->AddVector3f(tokens[1], new Vector3f((float)std::atof(tokens[2].c_str()), (float)std::atof(tokens[3].c_str())
								, (float)std::atof(tokens[4].c_str())));
						}
						else if (nameTokens[2] == "vec2")
						{
							material->AddVector2f(tokens[1], new Vector2f((float)std::atof(tokens[2].c_str()), (float)std::atof(tokens[3].c_str())));
						}
						else if (nameTokens[2] == "float")
						{
							material->AddFloat(tokens[1], new float((float)std::atof(tokens[2].c_str())));
						}
						else if (nameTokens[2] == "int")
						{
							material->AddInt(tokens[1], new int(std::atoi(tokens[2].c_str())));
						}
					}
				}
			}

			file.close();
		}
		else
		{
			PR_LOG_ERROR("File %s cannot be opened!\n", path.c_str());
		}
	}

	int TerrainConfig::UpdateMorphingArea(int lod)
	{
		return (int)((scaleXZ / TerrainQuadtree::rootNodes) / pow(2, lod));
	}
};