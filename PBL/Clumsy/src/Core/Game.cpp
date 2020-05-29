#include "../pch.h"

#include <yaml.h>

#include "Game.h"
#include "../RenderEngine/Model.h"
#include "../Components/RenderModelComponent.h"
#include "../Components/PhysicsObjectComponent.h"
#include "../Components/RenderInstancedModelComponent.h"


namespace Clumsy 
{	
	void Game::Render()
	{
		RenderEngine::GetInstance()->Render(m_Root); 
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

    void Game::SceneParser(GameObject* map)
    {
		AddToScene(map);
		std::vector<Transform> allTransforms;

		Model* m3 = new Model();//= new Model();
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
									k = it->second.as<std::string>();
									if (k.find("Pasture") != std::string::npos) {
										m3->loadModel("../Clumsy/src/models/jazda.obj");
									}
									if (k.find("Desert") != std::string::npos) {
										m3->loadModel("../Clumsy/src/models/jazda.obj");
									}
									if (k.find("Stone") != std::string::npos) {
										m3->loadModel("../Clumsy/src/models/jazda.obj");
									}
									if (k.find("Water") != std::string::npos) {
										m3->loadModel("../Clumsy/src/models/jazda.obj");
									}
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

						allTransforms.push_back(transform);

						glm::vec3 min = glm::vec3(transform.GetPos() - glm::vec3(0.5f, 0.1f, 0.8f));
						glm::vec3 max = glm::vec3(transform.GetPos() + glm::vec3(0.5f, 0.1f, 0.8f));
						PhysicsObject* pO = new PhysicsObject(new Aabb(min, max), &transform);
						PhysicsEngine::GetInstance()->AddObject(*pO);
						map->AddChild((new Clumsy::GameObject(transform))
							->AddComponent(new PhysicsObjectComponent(pO))); //delete addnig render model component
						//map->AddComponent(new Clumsy::RenderInstancedModelComponent(m3, allTransforms));


					}
				}
            }
        }
		map->AddComponent(new Clumsy::RenderInstancedModelComponent(m3, allTransforms));

    }

	void Game::ProcessInput(int input) 
	{
		m_Root.ProcessInputAll(input);
	}

}