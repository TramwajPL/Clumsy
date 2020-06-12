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
		RenderEngine::GetInstance()->GetPostProcessor()->BeginRender();
		RenderEngine::GetInstance()->Render(m_Root); 
		RenderEngine::GetInstance()->GetPostProcessor()->EndRender();
		RenderEngine::GetInstance()->GetPostProcessor()->Render(glfwGetTime());
		RenderEngine::GetInstance()->RenderGUI();
	}

	void Game::Update(float deltaTime)
	{
		m_Root.UpdateAll();
		if (RenderEngine::GetInstance()->GetShakeTime() > 0.0f)
		{
			RenderEngine::GetInstance()->SetShakeTime(RenderEngine::GetInstance()->GetShakeTime() - deltaTime);
			if (RenderEngine::GetInstance()->GetShakeTime() <= 0.0f)
				Clumsy::RenderEngine::GetInstance()->GetPostProcessor()->m_Shake = false;
		}
		if (RenderEngine::GetInstance()->m_Movement)
		{
			glm::vec3 currentPos = RenderEngine::GetInstance()->GetCurrentPlayer()->m_Transform.GetPos();
			glm::vec3 delta = RenderEngine::GetInstance()->GetDeltaMove();
			glm::vec3 destination = RenderEngine::GetInstance()->GetDestination();
			if (glm::length(currentPos - destination) > 0.001f)
			{
				glm::vec3 pos = RenderEngine::GetInstance()->GetCurrentPlayer()->m_Transform.GetPos();
				glm::vec3 newpos = pos + delta;
				RenderEngine::GetInstance()->GetCurrentPlayer()->m_Transform.SetPos(newpos);
				if (glm::length(pos - destination) <= 0.001f)
				{
					RenderEngine::GetInstance()->GetCurrentPlayer()->m_Transform.SetPos(destination);
					RenderEngine::GetInstance()->m_Movement = false;
				}
			}
		}
	}

	void Game::AddToScene(GameObject* child)
	{
		m_Root.AddChild(child);
	}

    std::string path = "../Clumsy/src/models/";

    void Game::SceneParser(GameObject* map, std::string filename)
    {
		AddToScene(map);
		std::vector<Transform> allTransformsM3;
		std::vector<Transform> allTransformsM4;
		std::vector<Transform> allTransformsM5;
		std::vector<Transform> allTransformsM6;
		Model* m3 = new Model();
		Model* m4 = new Model();
		Model* m5 = new Model();
		Model* m6 = new Model();
		Model* m7 = new Model();
		bool model3 = false;
		bool model4 = false;
		bool model5 = false;
		bool model6 = false;
        std::vector<YAML::Node> nodes = YAML::LoadAllFromFile(filename);
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]["PrefabInstance"]) {
				if (nodes[i]["PrefabInstance"]["m_Modification"]) {
					if (nodes[i]["PrefabInstance"]["m_Modification"]["m_Modifications"]) {
						bool firstNode = true;
						std::vector<float> values;
						std::string k;
						Transform transform;
						Transform transform2;
						for (YAML::iterator it = nodes[i]["PrefabInstance"]["m_Modification"]["m_Modifications"].begin(); it != nodes[i]["PrefabInstance"]["m_Modification"]["m_Modifications"].end(); ++it) {
							if (firstNode) {
								if (it->first.as<std::string>() == "value") {
									k = it->second.as<std::string>();
									if (k.find("Pasture") != std::string::npos) {
										m3->loadModel("../Clumsy/src/models/hexes/groundEarth_base_color.obj");
										model3 = true;
									}
									if (k.find("Desert") != std::string::npos) {
										m4->loadModel("../Clumsy/src/models/hexes/Desert_ground_Albedo.obj");
										model4 = true;
									}
									if (k.find("Stone") != std::string::npos) {
										m5->loadModel("../Clumsy/src/models/hexes/Stone_Albedo.obj");
										model5 = true;
									}
									if (k.find("Water") != std::string::npos) {
										m6->loadModel("../Clumsy/src/models/hexes/Water_Albedo.obj");
										model6 = true;
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

						if (model3) {
							transform.SetPosX(values[0]);
							transform.SetPosY(values[1]);
							transform.SetPosZ(values[2]);
							transform.SetRotX(0.0f);
							transform.SetRotY(0.7f);
							transform.SetRotZ(0.7f);
							transform.SetRotW(0.0f);
							transform.SetScale(0.0001f);

							allTransformsM3.push_back(transform);
							glm::vec3 min = glm::vec3(transform.GetPos() - glm::vec3(0.4f, 0.1f, 0.4f));
							glm::vec3 max = glm::vec3(transform.GetPos() + glm::vec3(0.4f, 0.1f, 0.4f));
							PhysicsObject* pO = new PhysicsObject(new Aabb(min, max), &transform);
							PhysicsEngine::GetInstance()->AddObject(*pO);
							GameObject* pasture = new GameObject(transform);
							map->AddChild((pasture)->AddComponent(new PhysicsObjectComponent(pO)));

							transform2.SetPosX(values[0]);
							transform2.SetPosY(values[1]);
							transform2.SetPosZ(values[2]);
							transform2.SetRotX(0.0f);//0
							transform2.SetRotY(0.7f);//0
							transform2.SetRotZ(0.7f);//0
							transform2.SetRotW(0.0f);//1
							transform2.SetScale(0.3f);

							glm::vec3 min2 = glm::vec3(transform2.GetPos() - glm::vec3(0.4f, 0.1f, 0.4f));
							glm::vec3 max2 = glm::vec3(transform2.GetPos() + glm::vec3(0.4f, 0.1f, 0.4f));
							PhysicsObject* pO2 = new PhysicsObject(new Aabb(min2, max2), &transform2);
							PhysicsEngine::GetInstance()->AddObject(*pO2);
							GameObject* tree = new GameObject(transform2);
							tree->SetM_Tag("tree");
							m7->loadModel("../Clumsy/src/models/hexes/tree_Oliwiw.obj");
							map->AddChild((tree)->AddComponent(new RenderModelComponent(m7, transform2))->AddComponent(new PhysicsObjectComponent(pO2)));
							model3 = false;
						}

						if (model4) {
							transform.SetPosX(values[0]);
							transform.SetPosY(values[1]);
							transform.SetPosZ(values[2]);
							transform.SetRotX(0.0f);//0
							transform.SetRotY(0.7f);//0
							transform.SetRotZ(0.7f);//0
							transform.SetRotW(0.0f);//1
							transform.SetScale(0.0001f);

							allTransformsM4.push_back(transform);
							glm::vec3 min = glm::vec3(transform.GetPos() - glm::vec3(0.4f, 0.1f, 0.4f));
							glm::vec3 max = glm::vec3(transform.GetPos() + glm::vec3(0.4f, 0.1f, 0.4f));
							PhysicsObject* pO = new PhysicsObject(new Aabb(min, max), &transform);
							PhysicsEngine::GetInstance()->AddObject(*pO);
							map->AddChild((new Clumsy::GameObject(transform))
								->AddComponent(new PhysicsObjectComponent(pO)));
							model4 = false;
						}
						if (model5) {
							transform.SetPosX(values[0]);
							transform.SetPosY(values[1]);
							transform.SetPosZ(values[2]);
							transform.SetRotX(0.0f);//0
							transform.SetRotY(0.7f);//0
							transform.SetRotZ(0.7f);//0
							transform.SetRotW(0.0f);//1
							transform.SetScale(0.0001f);

							allTransformsM5.push_back(transform);
							glm::vec3 min = glm::vec3(transform.GetPos() - glm::vec3(0.4f, 0.1f, 0.4f));
							glm::vec3 max = glm::vec3(transform.GetPos() + glm::vec3(0.4f, 0.1f, 0.4f));
							PhysicsObject* pO = new PhysicsObject(new Aabb(min, max), &transform);
							PhysicsEngine::GetInstance()->AddObject(*pO);
							map->AddChild((new Clumsy::GameObject(transform))
								->AddComponent(new PhysicsObjectComponent(pO)));
							model5 = false;
						}
						if (model6) {
							transform.SetPosX(values[0]);
							transform.SetPosY(values[1]);
							transform.SetPosZ(values[2]);
							transform.SetRotX(0.0f);//0
							transform.SetRotY(0.7f);//0
							transform.SetRotZ(0.7f);//0
							transform.SetRotW(0.0f);//1
							transform.SetScale(0.0001f);

							allTransformsM6.push_back(transform);
							glm::vec3 min = glm::vec3(transform.GetPos() - glm::vec3(0.4f, 0.1f, 0.4f));
							glm::vec3 max = glm::vec3(transform.GetPos() + glm::vec3(0.4f, 0.1f, 0.4f));
							PhysicsObject* pO = new PhysicsObject(new Aabb(min, max), &transform);
							PhysicsEngine::GetInstance()->AddObject(*pO);
							map->AddChild((new Clumsy::GameObject(transform))
								->AddComponent(new PhysicsObjectComponent(pO)));
							model6 = false;
						}
					}
				}
            }
        }
		map->AddComponent(new Clumsy::RenderInstancedModelComponent(m3, allTransformsM3));
		map->AddComponent(new Clumsy::RenderInstancedModelComponent(m4, allTransformsM4));
		map->AddComponent(new Clumsy::RenderInstancedModelComponent(m5, allTransformsM5));
		map->AddComponent(new Clumsy::RenderInstancedModelComponent(m6, allTransformsM6));
    }

	void Game::ProcessInput(int input) 
	{
		m_Root.ProcessInputAll(input);
	}

}