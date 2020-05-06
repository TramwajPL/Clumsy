#include "../pch.h"
#include "yaml.h"
#include "Game.h"
#include "../RenderEngine/Model.h"
#include "../Components/RenderModelComponent.h"

namespace Clumsy {
	//Input* Input::s_Instance = nullptr;

	//void Game::ProcessInput(const Input& input)
	//{
		/*if (m_Input->GetKeyDown(Input::KEY_UP))
		{
			std::cout << "WE PRESSED UP!";
		}*/
	//}
	
	void Game::Render(RenderEngine* renderingEngine)
	{
		renderingEngine->Render(m_Root); 
	}

	void Game::Update()
	{
		m_Root.UpdateAll();
	}

	void Game::AddToScene(GameObject* child)
	{
		m_Root.AddChild(child);
	}

    std::string path = "../Clumsy/src/models/";

    void Game::SceneParser()
    {
		Model m1("../Clumsy/src/models/jazda.obj");
        std::vector<YAML::Node> nodes = YAML::LoadAllFromFile("Test.unity");
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]["PrefabInstance"]) {
				if (nodes[i]["PrefabInstance"]["m_Modification"]) {
					if (nodes[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]) {
						bool firstNode = true;
						std::vector<float> values;
						std::string k;
						Transform transform;
						for (YAML::iterator it = nodes[i]["PrefabInstance"]["m_Modification"]["m_Modifications"].begin(); it != nodes[i]["PrefabInstance"]["m_Modification"]["m_Modifications"].end(); ++it) {
							if (firstNode) {
								if (it->first.as<std::string>() == "value") {
									firstNode = false;
								}
							}
							else {
								if (it->first.as<std::string>() == "value") {
									values.push_back(it->second.as<float>());
								}
							}
						}
						values.pop_back();
						values.pop_back();
						values.pop_back();
						values.pop_back();
						transform.SetPosX(values[0]);
						transform.SetPosY(values[1]);
						transform.SetPosZ(values[2]);
						transform.SetRotX(values[3]);
						transform.SetRotY(values[4]);
						transform.SetRotZ(values[5]);
						transform.SetRotW(values[6]);
						transform.SetScale(0.0001f);
						AddToScene((new Clumsy::GameObject(transform))->AddComponent(new Clumsy::RenderModelComponent(m1, transform)));
					}
				}
            }
        }
    }

	void Game::ProcessInput(int input) {
		m_Root.ProcessInputAll(input);
	}

}