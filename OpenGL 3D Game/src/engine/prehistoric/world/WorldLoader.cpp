#include "engine/prehistoric/core/util/Includes.hpp"
#include "WorldLoader.h"

#include "engine/prehistoric/resources/AssembledAssetManager.h"

void WorldLoader::LoadWorld(const std::string& worldFile, GameObject* root, Window* window, AssembledAssetManager* manager)
{
	std::ifstream file;
	file.open(worldFile.c_str());

	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			std::vector<std::string> tokens = Util::Split(line, ' ');
			std::vector<std::string> nameTokens = Util::Split(tokens[0], '.');

			if (tokens.size() == 0 || nameTokens[0] == "#")
				continue;

			//Setting the directories which we'll be using to load models and textures from
			if (nameTokens[0] == "directories")
			{
				if (nameTokens[1] == "models")
				{
					directoryModels = tokens[1];
				}
				if (nameTokens[1] == "textures")
				{
					directoryTextures = tokens[1];
				}
			}

			//Loading models and texture
			if (nameTokens[0] == "models")
			{
				if (nameTokens[1] == "load")
				{
					models.insert(std::make_pair(tokens[2], manager->getAssetManager()->getResource<VertexBuffer>(tokens[2])));
				}
			}
			if (nameTokens[0] == "textures")
			{
				if (nameTokens[1] == "load")
				{
					textures.insert(std::make_pair(tokens[1], manager->getAssetManager()->getResource<Texture>(tokens[2])));
				}
			}

			//Creating materials from textures and other data
			if (nameTokens[0] == "materials")
			{
				if (nameTokens[1] == "add")
				{
					Material* material = new Material(manager->getAssetManager(), window);
					materials.insert(std::make_pair(tokens[1], material));
				}
				else
				{
					auto index = materials.find(nameTokens[1]);

					if (index == materials.end())
					{
						PR_LOG_ERROR("Material (name: %s) does not exist, or haven't been created in the world file!\n", nameTokens[1].c_str());
						continue;
					}

					Material* material = materials.at(nameTokens[1]);
					
					if (nameTokens[2] == "texture")
					{
						auto index = textures.find(tokens[2]);

						if (index == textures.end())
						{
							PR_LOG_ERROR("Texture (name: %s) does not exist, or haven't been created in the world file!\n", tokens[1].c_str());
							continue;
						}

						material->addTexture(tokens[1] + "Map", textures.at(tokens[2]));
					}

					if (nameTokens[2] == "vec4")
					{
						std::vector<std::string> compTokens = Util::Split(tokens[2], ',');

						Vector4f value = Vector4f((float) std::atof(compTokens[0].c_str()), (float) std::atof(compTokens[1].c_str()), (float) std::atof(compTokens[2].c_str()), (float) std::atof(compTokens[3].c_str()));
						material->addVector4f(tokens[1], value);
					}
					if (nameTokens[2] == "vec3")
					{
						std::vector<std::string> compTokens = Util::Split(tokens[2], ',');

						Vector3f value = Vector3f((float) std::atof(compTokens[0].c_str()), (float) std::atof(compTokens[1].c_str()), (float) std::atof(compTokens[2].c_str()));
						material->addVector3f(tokens[1], value);
					}
					if (nameTokens[2] == "vec2")
					{
						std::vector<std::string> compTokens = Util::Split(tokens[2], ',');

						Vector2f value = Vector2f((float) std::atof(compTokens[0].c_str()), (float) std::atof(compTokens[1].c_str()));
						material->addVector2f(tokens[1], value);
					}

					if (nameTokens[2] == "float")
					{
						float value = static_cast<float>(std::atof(tokens[2].c_str()));
						material->addFloat(tokens[1], value);
					}
					if (nameTokens[2] == "int")
					{
						int value = std::atoi(tokens[2].c_str());
						material->addInt(tokens[1], value);
					}
				}
			}

			//Creating GameObjects
			if (nameTokens[0] == "world")
			{
				if (nameTokens[1] == "object")
				{
					if (nameTokens.size() < 3)
					{
						GameObject* obj = new GameObject();

						if (tokens.size() > 2)
						{
							std::vector<std::string> compTokens = Util::Split(tokens[2], ',');
							obj->SetPosition({ (float) std::atof(compTokens[0].c_str()), (float) std::atof(compTokens[1].c_str()), (float) std::atof(compTokens[2].c_str()) });
						}
						if (tokens.size() > 3)
						{
							std::vector<std::string> compTokens = Util::Split(tokens[3], ',');
							obj->SetRotation({ (float)(float) std::atof(compTokens[0].c_str()), (float) std::atof(compTokens[1].c_str()), (float) std::atof(compTokens[2].c_str()) });
						}
						if (tokens.size() > 4)
						{
							std::vector<std::string> compTokens = Util::Split(tokens[4], ',');
							obj->SetScale({ (float) std::atof(compTokens[0].c_str()), (float) std::atof(compTokens[1].c_str()), (float) std::atof(compTokens[2].c_str()) });
						}

						root->AddChild(tokens[1], obj);
					}
					else
					{
						int i = 2;
						GameObject* objToAdd = root;
						while (true)
						{
							objToAdd = reinterpret_cast<GameObject*>(objToAdd->getChildren()[nameTokens[i]]);
							i++;

							if(nameTokens.size() < (size_t(i) + 1))
							{
								GameObject* obj = new GameObject();

								if (tokens.size() > 2)
								{
									std::vector<std::string> compTokens = Util::Split(tokens[2], ',');
									obj->SetPosition({ (float) std::atof(compTokens[0].c_str()), (float) std::atof(compTokens[1].c_str()), (float) std::atof(compTokens[2].c_str()) });
								}
								if (tokens.size() > 3)
								{
									std::vector<std::string> compTokens = Util::Split(tokens[3], ',');
									obj->SetRotation({ (float)std::atof(compTokens[0].c_str()), (float)std::atof(compTokens[1].c_str()), (float)std::atof(compTokens[2].c_str()) });
								}
								if (tokens.size() > 4)
								{
									std::vector<std::string> compTokens = Util::Split(tokens[4], ',');
									obj->SetScale({ (float)std::atof(compTokens[0].c_str()), (float)std::atof(compTokens[1].c_str()), (float)std::atof(compTokens[2].c_str()) });
								}

								objToAdd->AddChild(tokens[1], obj);

								break;
							}
						}
					}
				}
			}

			//Adding components to objects
			if (nameTokens[0] == "object")
			{
				auto list = root->getChildren();

				auto index = list.find(nameTokens[1]);

				if (index == list.end())
				{
					PR_LOG_ERROR("GameObject (name: %s) does not exist, or haven't been created in the world file!\n", nameTokens[1].c_str());
					continue;
				}

				GameObject* obj = reinterpret_cast<GameObject*>(list[nameTokens[1]]);

				if (nameTokens[2] == "component")
				{
					if (tokens[1] == "RendererComponent")
					{
 						std::vector<std::string> compTokens = Util::Split(tokens[2], ',');

						size_t vboID = models.at(compTokens[0]);
						size_t shaderID = -1;

						Material* material = materials.at(compTokens[2]);
						Pipeline* pipeline = nullptr;

						auto shaderIndex = shaders.find(compTokens[1]);
						if (shaderIndex != shaders.end())
						{
							shaderID = shaderIndex->second;
						}
						else
						{
							Shader* shader = nullptr;
							shaders.insert(std::make_pair(compTokens[1], manager->getAssetManager()->getResource<Shader>(compTokens[1])));
						}

						auto pipelineIndex = pipelines.find(compTokens[0] + "," + compTokens[1]);
						if (pipelineIndex != pipelines.end())
						{
							pipeline = pipelineIndex->second;
						}
						else
						{
							Pipeline* pipeline = nullptr;

							if (FrameworkConfig::api == OpenGL)
							{
								pipeline = new GLGraphicsPipeline(window, manager->getAssetManager(), shaderID, vboID);

								reinterpret_cast<GLGraphicsPipeline*>(pipeline)->SetBackfaceCulling(true);
							}
							else if (FrameworkConfig::api == Vulkan)
							{
								pipeline = new VKGraphicsPipeline(window, manager->getAssetManager(), shaderID, vboID);

								reinterpret_cast<VKGraphicsPipeline*>(pipeline)->SetBackfaceCulling(false);;
							}

							pipelines.insert(std::make_pair(compTokens[0] + "," + compTokens[1], pipeline));
						}

						RendererComponent* renderer = new RendererComponent(pipeline, material, window, manager);

						obj->AddComponent(tokens[1], renderer);
					}
					if (tokens[1] == "Light")
					{
						std::vector<std::string> compTokens = Util::Split(tokens[2], ';');

						Light* light = new Light();

						std::vector<std::string> posTokens = Util::Split(compTokens[0], ',');
						light->setColour({ (float) std::atof(posTokens[0].c_str()), (float)std::atof(posTokens[1].c_str()), (float)std::atof(posTokens[2].c_str()) });

						light->setIntensity((float) std::atof(compTokens[1].c_str()));

						obj->AddComponent("Light", light);
					}
				}
				else
				{
					int i = 2;
					GameObject* objToAdd = obj;
					while (true)
					{
						auto list = objToAdd->getChildren();

						auto index = list.find(nameTokens[i]);

						if (index == list.end())
						{
							PR_LOG_ERROR("GameObject (name: %s) does not exist, or haven't been created in the world file!\n", nameTokens[i].c_str());
							continue;
						}

						objToAdd = reinterpret_cast<GameObject*>(list[nameTokens[1]]);
						i++;

						if (nameTokens[i] == "component")
						{
							if (tokens[1] == "RendererComponent")
							{
								std::vector<std::string> compTokens = Util::Split(tokens[2], ',');

								size_t vboID = models.at(compTokens[0]);
								size_t shaderID = -1;

								Material* material = materials.at(compTokens[2]);
								Pipeline* pipeline = nullptr;

								auto shaderIndex = shaders.find(compTokens[1]);
								if (shaderIndex != shaders.end())
								{
									shaderID = shaderIndex->second;
								}
								else
								{
									shaders.insert(std::make_pair(compTokens[1], manager->getAssetManager()->getResource<Shader>(compTokens[1])));
								}

								auto pipelineIndex = pipelines.find(compTokens[0] + "," + compTokens[1]);
								if (pipelineIndex != pipelines.end())
								{
									pipeline = pipelineIndex->second;
								}
								else
								{
									Pipeline* pipeline = nullptr;

									if (FrameworkConfig::api == OpenGL)
									{
										pipeline = new GLGraphicsPipeline(window, manager->getAssetManager(), shaderID, vboID);

										reinterpret_cast<GLGraphicsPipeline*>(pipeline)->SetBackfaceCulling(true);
									}
									else if (FrameworkConfig::api == Vulkan)
									{
										pipeline = new VKGraphicsPipeline(window, manager->getAssetManager(), shaderID, vboID);

										reinterpret_cast<VKGraphicsPipeline*>(pipeline)->SetBackfaceCulling(false);;
									}

									pipelines.insert(std::make_pair(compTokens[0] + "," + compTokens[1], pipeline));
								}

								RendererComponent* renderer = new RendererComponent(pipeline, material, window, manager);

								obj->AddComponent(tokens[1], renderer);

								break;
							}
							if (tokens[1] == "Light")
							{
								std::vector<std::string> compTokens = Util::Split(tokens[2], ';');

								Light* light = new Light();

								std::vector<std::string> posTokens = Util::Split(compTokens[0], ',');
								light->setColour({ (float)std::atof(posTokens[0].c_str()), (float)std::atof(posTokens[1].c_str()), (float)std::atof(posTokens[2].c_str()) });

								light->setIntensity((float)std::atof(compTokens[1].c_str()));

								objToAdd->AddComponent("Light", light);

								break;
							}
						}
						else
						{
							continue;
						}
					}
				}
			}
		}
	}
	else
	{
		PR_LOG_ERROR("Could not open world file %s!\n", worldFile.c_str());
	}
}