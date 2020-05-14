#include "../pch.h"

#include <yaml.h>

#include "Game.h"
#include "../RenderEngine/Model.h"
#include "../Components/RenderModelComponent.h"
#include "../Components/PhysicsObjectComponent.h"

namespace Clumsy 
{	
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

    void Game::SceneParser(PhysicsEngine* physicsEngine, GameObject* map)
    {
		AddToScene(map);
		Model m3;//= new Model();
		m3.loadModel("../Clumsy/src/models/jazda.obj");
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
						transform.SetRotX(0.0f);//0
						transform.SetRotY(0.7f);//0
						transform.SetRotZ(0.7f);//0
						transform.SetRotW(0.0f);//1
						transform.SetScale(0.0001f);
						glm::vec3 min = glm::vec3(transform.GetPos() - glm::vec3(0.5f, 0.1f, 0.8f));
						glm::vec3 max = glm::vec3(transform.GetPos() + glm::vec3(0.5f, 0.1f, 0.8f));
						PhysicsObject* pO = new PhysicsObject(new Aabb(min, max), &transform);
						physicsEngine->AddObject(*pO);
						map->AddChild((new Clumsy::GameObject(transform))->AddComponent(new Clumsy::RenderModelComponent(&m3, transform))
							->AddComponent(new PhysicsObjectComponent(pO)));
					}
				}
            }
        }
    }

	void Game::ProcessInput(int input) 
	{
		m_Root.ProcessInputAll(input);
	}

}