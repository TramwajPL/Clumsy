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
                //Enemy spawns random number of trees (when he exists)
                if (enemyOnBoard)
                {
                    if (callsController > 0)
                    {
                        SpawnTrees();
                        callsController--;
                    }

                }
                //Spawn one tree every 4 turns
                if (callsController2 > 0 && TurnSystem::GetInstance()->GetTurnCounter() % 4 == 2)
                {
                    if (TurnSystem::GetInstance()->GetTurnCounter() > 5)
                    {
                        SpawnTrees2();
                    }
                    //TreePositionIndicator();
                    callsController2--;
                }
                std::cout << " Nature time! " << std::endl;
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