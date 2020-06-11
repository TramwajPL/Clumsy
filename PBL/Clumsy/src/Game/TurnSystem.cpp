#include "../pch.h"

#include "TurnSystem.h"

namespace Clumsy
{
	TurnSystem::TurnSystem()
	{
        ResetTurns();
	}

    TurnSystem* TurnSystem::GetInstance()
    {
        if (!m_Instance)
            m_Instance = new TurnSystem;
        return m_Instance;
    }

	void TurnSystem::ResetTurns()
	{
        for (int i = 0; i < players.size(); i++)
        {
            if (i == 0)
            {
                players[i].isTurn = true;
                players[i].wasTurnPrev = false;
            }
            else
            {
                players[i].isTurn = false;
                players[i].wasTurnPrev = false;
            }
        }
        m_TurnCounter++;
	}

    void TurnSystem::Update()
    {
        UpdateTurns();
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i].isTurn)
                m_ActivePlayer = players[i].GetGameObject();
        }
    }

    void TurnSystem::UpdateTurns()
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (!players[i].wasTurnPrev)
            {
                players[i].isTurn = true;
                break;
            }
            else if (i == players.size() - 1 && players[i].wasTurnPrev)
            {
                ResetTurns();
            }
        }
    }

    GameObject* TurnSystem::GetActivePlayer()
    {
        return m_ActivePlayer;
    }

    void TurnSystem::AddPlayer(GameObject* player)
    {
        players.push_back(TurnClass(player));
    }

    void TurnSystem::DeletePlayer(GameObject* player)
    {
        for (std::vector<TurnClass>::iterator b = players.begin(); b != players.end(); ++b)
        {
            if (b->GetGameObject() == player)
            {
                b = players.erase(b);
            }
        }
    }
}