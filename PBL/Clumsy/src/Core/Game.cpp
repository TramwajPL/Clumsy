#include "../pch.h"
#include "yaml.h"
#include "Game.h"
#include "../RenderEngine/Model.h"
#include "../Components/RenderModelComponent.h"

namespace Clumsy {
	//Input* Input::s_Instance = nullptr;

	void Game::ProcessInput(const Input& input)
	{
		/*if (m_Input->GetKeyDown(Input::KEY_UP))
		{
			std::cout << "WE PRESSED UP!";
		}*/
	}
	
	void Game::Render(RenderEngine* renderingEngine)
	{
		renderingEngine->Render(m_Root); //TODO
	}

	void Game::AddToScene(GameObject* child)
	{
		m_Root.AddChild(child);
	}

    std::string path = "../Clumsy/src/models/";
    /*void Game::SceneParser()
    {
		std::vector<std::string> levels;
        std::vector<YAML::Node> config = YAML::LoadAllFromFile("Test.unity");
        for (int i = 0; i < config.size(); i++) {
            if (config[i]["PrefabInstance"]) {
                    Transform transform;
					Model* m1;
					if (config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["propertyPath"].as<std::string> == "m_Name") {
						m1 = new Model(path + config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["value"].as<std::string>());
					}

					if (config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["propertyPath"].as<std::string> == "m_LocalPosition.x") {
						transform.SetPosX(config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["value"].as<float>());
					}

					if (config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["propertyPath"].as<std::string> == "m_LocalPosition.y") {
						transform.SetPosY(config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["value"].as<float>());
					}

					if (config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["propertyPath"].as<std::string> == "m_LocalPosition.z") {
						transform.SetPosZ(config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["value"].as<float>());
					}

					if (config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["propertyPath"].as<std::string> == "m_LocalRotation.x") {
						transform.SetRotX(config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["value"].as<float>());
					}

					if (config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["propertyPath"].as<std::string> == "m_LocalRotation.y") {
						transform.SetRotY(config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["value"].as<float>());
					}

					if (config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["propertyPath"].as<std::string> == "m_LocalRotation.z") {
						transform.SetRotZ(config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["value"].as<float>());
					}

					if (config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["propertyPath"].as<std::string> == "m_LocalRotation.w") {
						transform.SetRotW(config[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]["value"].as<float>());
					}

					AddToScene((new GameObject(transform))->AddComponent(new RenderModelComponent(*m1, transform)));

            }
        }
    }*/
}