#pragma once
#include "../pch.h"
#include <cstdlib>
#include <glm/gtx/string_cast.hpp>
#include "../Game/TurnSystem.h"
#include "../Core/GameObject.h"

namespace Clumsy
{
	class Nature : public GameObject
	{
	public:
		Nature() : GameObject() 
        {
            srand(time(NULL));
            listOfPosition = new std::vector<glm::vec3>();
        }
		
        ~Nature() {}

		void SetTurnClass(TurnClass* tc) { m_TurnClass = tc; }

        void SetEnemyPreset(bool b) { enemyOnBoard = b; }

		void UpdateTurn()
		{
			isTurn = m_TurnClass->isTurn;
            if (!isTurn)
            {
                //To change number of spawned trees change these values
                callsController = rand() % (listOfPosition->size() - 1);
                callsController2 = 1;
            }
            if (isTurn)
            {
                std::cout << "turn... " << std::endl;
                if (Clumsy::RenderEngine::GetInstance()->enemy->getIfActive()) 
                {
                    // movement
                    bool moved = false;
                    int chance = 0;
                    while (!moved || chance < 5)
                    {
                        moved = EntMovement();
                        chance++;
                    }
                    // respawn
					int randomNumber = (rand() % 5) + 1;
					for (int i = 0; i < randomNumber ; i++)
					{
						SpawnOneTree();
					}
                }

                if (TurnSystem::GetInstance()->GetTurnCounter() % 2 == 0)
                {
                    SpawnOneTree();
                }
                std::cout << " Nature time! " << std::endl;
                std::cout << "Tura nr: " << TurnSystem::GetInstance()->GetTurnCounter() << std::endl;
                isTurn = false;
                m_TurnClass->isTurn = isTurn;
                m_TurnClass->wasTurnPrev = true;
            }
		}

        void SpawnOneTree()
        {
            if (RenderEngine::GetInstance()->cutTreesTransforms.size() > 0) 
            {
                int RandomTreeToSpawn = rand() % RenderEngine::GetInstance()->cutTreesTransforms.size();
                // check if tile occupied
                bool occupied = false;
                for (int i = 0; i < TurnSystem::GetInstance()->GetPlayers().size(); i++)
                {
                    Player* player = dynamic_cast<Player*>(TurnSystem::GetInstance()->GetPlayers()[i]->GetGameObject());
                    if (player)
                    {
                        if (glm::length(player->m_Rmc->m_Transform.GetPos() - RenderEngine::GetInstance()->cutTreesTransforms[RandomTreeToSpawn].GetPos()) < 0.1f
                            || glm::length(RenderEngine::GetInstance()->GetDestination() - RenderEngine::GetInstance()->cutTreesTransforms[RandomTreeToSpawn].GetPos()) < 0.1f)
                        {
                            occupied = true;
                            std::cout << "bez drzewa!" << std::endl;
                            break;
                        }
                    }
                }
                if (!occupied)
                {
                    RenderEngine::GetInstance()->treeTransforms.push_back(RenderEngine::GetInstance()->cutTreesTransforms.at(RandomTreeToSpawn));
                    RenderEngine::GetInstance()->cutTreesTransforms.erase(RenderEngine::GetInstance()->cutTreesTransforms.begin() + RandomTreeToSpawn);
                }
            }
        }

        bool EntMovement()
        {
            if (RenderEngine::GetInstance()->groundSand.size() > 0)
            {
                int number = rand() % RenderEngine::GetInstance()->groundSand.size();
                glm::vec3* destination = &RenderEngine::GetInstance()->groundSand[number].GetPos();
                std::cout << "destination ent " << glm::to_string(*destination) << std::endl;
                glm::vec3* currentpos = &RenderEngine::GetInstance()->enemy->m_Rmc->m_Transform.GetPos();
                std::cout << "position ent " << glm::to_string(*currentpos) << std::endl;
                if (glm::length(*currentpos - *destination) < 2.5f)
                {
                    // move
                    glm::vec3 delta = (*destination - *currentpos) * glm::vec3(0.1f);
                    Clumsy::RenderEngine::GetInstance()->SetEnemyDestination(*destination);
                    Clumsy::RenderEngine::GetInstance()->SetEnemyDeltaMove(delta);
                    Clumsy::RenderEngine::GetInstance()->m_EnemyMovement = true;
                    return true;
                }
            }
            else if (RenderEngine::GetInstance()->cutTreesTransforms.size() > 0)
            {
                int number = rand() % RenderEngine::GetInstance()->cutTreesTransforms.size();
                glm::vec3* destination = &RenderEngine::GetInstance()->cutTreesTransforms[number].GetPos();
                std::cout << "destination ent " << glm::to_string(*destination) << std::endl;
                glm::vec3* currentpos = &RenderEngine::GetInstance()->enemy->m_Rmc->m_Transform.GetPos();
                std::cout << "position ent " << glm::to_string(*currentpos) << std::endl;
                if (glm::length(*currentpos - *destination) < 2.5f)
                {
                    // move
                    glm::vec3 delta = (*destination - *currentpos) * glm::vec3(0.1f);
                    Clumsy::RenderEngine::GetInstance()->SetEnemyDestination(*destination);
                    Clumsy::RenderEngine::GetInstance()->SetEnemyDeltaMove(delta);
                    Clumsy::RenderEngine::GetInstance()->m_EnemyMovement = true;
                    return true;
                }
            }
            return false;
        }
        
	private:
		bool isTurn = false;
		bool enemyOnBoard = false;
		TurnClass* m_TurnClass = nullptr;

        int callsController = 0;
        int callsController2 = 1;
        std::vector<glm::vec3>* listOfPosition;
	};
}