#pragma once
#include "../pch.h"
#include <cstdlib>
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

                //ENEMY SPAWNS ONE TREE EVERY ONE TURN
                if (Clumsy::RenderEngine::GetInstance()->enemy->getIfActive()) {
					int randomNumber = (rand() % 5) + 1; //range from 1 to 10
					for (int i = 0; i < randomNumber ; i++)
					{
						SpawnOneTreeEnemy();
					}
                }

                if (TurnSystem::GetInstance()->GetTurnCounter() % 2 == 2)
                {
                    SpawnOneTree();
                }

                ////Spawn one tree every 4 turns
                //if (callsController2 > 0 && TurnSystem::GetInstance()->GetTurnCounter() % 4 == 2)
                //{
                //    if (TurnSystem::GetInstance()->GetTurnCounter() > 5)
                //    {
                //        SpawnTrees2();
                //    }
                //    //TreePositionIndicator();
                //    callsController2--;
                //}
                std::cout << " Nature time! " << std::endl;
                std::cout << "Tura nr: " << TurnSystem::GetInstance()->GetTurnCounter() << std::endl;
                isTurn = false;
                m_TurnClass->isTurn = isTurn;
                m_TurnClass->wasTurnPrev = true;
            }
		}

        void SpawnTrees()
        {
            /*if (listOfPosition.Count > 0)
            {
                int currentPosition = Random.Range(0, listOfPosition.Count);
                Vector3 randomTreePosition = listOfPosition[currentPosition];
                if (randomTreePosition.x != player.transform.position.x && randomTreePosition.z != player.transform.position.z)
                {
                    Transform treeTrans = Instantiate(hexTreePrefab, randomTreePosition, transform.rotation);
                    if (emptiedHexes[currentPosition] != null)
                    {
                        treeTrans.parent = emptiedHexes[currentPosition].transform;
                        hexTreePrefab.tag = "hover";
                        listOfPosition.RemoveAt(currentPosition);
                        emptiedHexes.RemoveAt(currentPosition);
                    }
                    else
                    {
                        Debug.Log("Blad");
                    }
                }
            }*/
        }

        void SpawnOneTree(){

            if (RenderEngine::GetInstance()->cutTreesTransforms.size() > 0) {
                int RandomTreeToSpawn = rand() % RenderEngine::GetInstance()->cutTreesTransforms.size();
                RenderEngine::GetInstance()->treeTransforms.push_back(RenderEngine::GetInstance()->cutTreesTransforms.at(RandomTreeToSpawn));
                RenderEngine::GetInstance()->cutTreesTransforms.erase(RenderEngine::GetInstance()->cutTreesTransforms.begin() + RandomTreeToSpawn);
				
            }
           }


		void SpawnOneTreeEnemy() {

			if (RenderEngine::GetInstance()->cutTreesTransforms.size() > 0) {
				int RandomTreeToSpawn = rand() % RenderEngine::GetInstance()->cutTreesTransforms.size();
				RenderEngine::GetInstance()->treeTransforms.push_back(RenderEngine::GetInstance()->cutTreesTransforms.at(RandomTreeToSpawn));
				RenderEngine::GetInstance()->SetSpawnTreePosition(RenderEngine::GetInstance()->cutTreesTransforms.at(RandomTreeToSpawn));
				RenderEngine::GetInstance()->enemySpawn = true;
				RenderEngine::GetInstance()->cutTreesTransforms.erase(RenderEngine::GetInstance()->cutTreesTransforms.begin() + RandomTreeToSpawn);
			}
		}

        void SpawnTrees2()
        {
           /* if (treePosition != null)
            {
                if (glowingHex != null)
                {
                    glowingHex.GetComponent<TreeIndicator>().particle.Stop();

                    Vector3 treePos = (Vector3)treePosition;
                    if (treePos.x != player.transform.position.x && treePos.z != player.transform.position.z)
                    {
                        Transform treeTrans = Instantiate(hexTreePrefab, treePos, transform.rotation);
                        treeTrans.parent = glowingHex.transform;
                        hexTreePrefab.tag = "hover";
                        treePosition = null;
                    }
                }
            }*/
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