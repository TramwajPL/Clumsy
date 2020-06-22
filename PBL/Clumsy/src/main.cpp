#include "pch.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Clumsy.h"

const unsigned int SCR_WIDTH = 1920;
//const unsigned int SCR_WIDTH = 1366;
//const unsigned int SCR_HEIGHT = 768;
const unsigned int SCR_HEIGHT = 1080;

Clumsy::GameObject* object1;
Clumsy::RenderModelComponent* rmc;
Clumsy::RenderModelComponent* enemyRmc; //enemy
bool isScrolled = false;
float iter = 0.0f;
Clumsy::AudioMaster* Clumsy::AudioMaster::m_Instance = 0;
Clumsy::EventSystem* Clumsy::EventSystem::m_Instance = 0;
Clumsy::PhysicsEngine* Clumsy::PhysicsEngine::m_Instance = 0;
Clumsy::RenderEngine* Clumsy::RenderEngine::m_Instance = 0;
Clumsy::TurnSystem* Clumsy::TurnSystem::m_Instance = 0;

class TestGame : public Clumsy::Game
{
public:
	TestGame(GLFWwindow* window, glm::vec3 playerPosition, glm::vec3 enemyPosition, std::string filename) :
		m_GLFWWindow(window),
		m_PlayerPos(playerPosition),
		m_EnemyPos(enemyPosition),
		m_Path(filename)
	{}

	virtual void Init()
	{
		Clumsy::RenderEngine::GetInstance()->SetXScaleBackground(10); //zmiana wielkoœci paska pod spodem (zielonego) czerwony zawsze dochodzi  tylko do jego koñca
		std::string filename = m_Path;

		SceneParser(Clumsy::RenderEngine::GetInstance()->map, filename);

		glm::vec3 pos = m_PlayerPos;
		glm::vec3 enemyPos = m_EnemyPos;

		glm::quat rotBoy = glm::angleAxis(glm::radians(-180.f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::quat rotEnemy = glm::angleAxis(glm::radians(-180.f), glm::vec3(1.0f, 0.0f, 0.0f));
		rotEnemy = glm::rotate(rotEnemy, glm::radians(180.f), glm::vec3(0.0f, 0.0f, 1.0f) * rotEnemy);

		float scale = 0.0001f;

		Clumsy::Transform boyTransform(pos, rotBoy, 0.1f);
		Clumsy::Transform enemyTransform(enemyPos, rotEnemy, 0.01); //enemy
					
		Clumsy::Player* boy = new Clumsy::Player(boyTransform);
		//Clumsy::RenderEngine::GetInstance()->boys.push_back(boy);

		Clumsy::RenderEngine::GetInstance()->enemy = new Clumsy::Enemy(Clumsy::RenderEngine::GetInstance()->enemyModel, enemyTransform); //enemy change how much we need to collect wood
		Clumsy::RenderEngine::GetInstance()->enemy->SetM_Tag("enemy"); //ost zmiana

		Clumsy::PhysicsObject* ob1 = new Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(boy->GetTransform().GetPos(), 0.1f), &boy->GetTransform());

		Clumsy::PhysicsObject* obEnemy = new Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(Clumsy::RenderEngine::GetInstance()->enemy->GetTransform().GetPos(), 0.1f),
			&Clumsy::RenderEngine::GetInstance()->enemy->GetTransform()); //enemy Collider //ost zmiana

		Clumsy::PhysicsEngine::GetInstance()->AddObject(*ob1);
		Clumsy::PhysicsEngine::GetInstance()->AddObject(*obEnemy); //enemy add Physic Component

		Clumsy::PhysicsEngineComponent* physicsEngineComponent
			= new Clumsy::PhysicsEngineComponent();
		//rmc = new Clumsy::RenderModelComponent(playerModel, boy->GetTransform(), 90.0f);
		enemyRmc = new Clumsy::RenderModelComponent(Clumsy::RenderEngine::GetInstance()->enemyModel, Clumsy::RenderEngine::GetInstance()->enemy->GetTransform(), 360.0f, true); //enemy RMC //ost zmiana

		Clumsy::RenderModelComponent* rmc1 = new Clumsy::RenderModelComponent(Clumsy::RenderEngine::GetInstance()->playerModel, boy->GetTransform(), 90);
		boy->m_Rmc = rmc1;
		Clumsy::Cube* c1 = new Clumsy::Cube(boyTransform);
		c1->SetPlayer(rmc1);
		Clumsy::RenderEngine::GetInstance()->AddCube(c1);

		AddToScene((boy)->AddComponent(rmc1));

		Clumsy::RenderEngine::GetInstance()->enemy->m_Rmc = enemyRmc;
		AddToScene((Clumsy::RenderEngine::GetInstance()->enemy)->AddComponent(enemyRmc)); //enemy Add to scene //ost zmiana

		boy->AddComponent(new Clumsy::PhysicsObjectComponent(ob1));
		Clumsy::RenderEngine::GetInstance()->enemy->AddComponent(new Clumsy::PhysicsObjectComponent(obEnemy)); //enemy //ost zmiana

		AddToScene((new Clumsy::GameObject())
			->AddComponent(physicsEngineComponent));

		Clumsy::Nature* nature = new Clumsy::Nature();

		Clumsy::TurnSystem::GetInstance()->AddPlayer(nature);
		Clumsy::TurnSystem::GetInstance()->AddPlayer(boy);

		Clumsy::AudioMaster::GetInstance()->PlayAmbientMusic();
	}

private:
	GLFWwindow* m_GLFWWindow;
	std::string m_Path;
	glm::vec3 m_PlayerPos, m_EnemyPos;
};


Clumsy::Camera* camera = new Clumsy::Camera(glm::vec3(0.0f, 13.0f, -8.0f));

Clumsy::Window* window = new Clumsy::Window(SCR_WIDTH, SCR_HEIGHT);

glm::mat4 projectionMP = glm::perspective(glm::radians(camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);

Clumsy::MousePicker mp(camera, window, projectionMP);

glm::vec3 v1 = glm::vec3(0.0f, 0.0f, -2.0f) - glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 v2 = glm::vec3(0.0f, 0.0f, -2.0f) + glm::vec3(1.0f, 1.0f, 1.0f);

Clumsy::Aabb a1(v1, v2);

GLFWwindow* glfwWindow = window->GetGLFWWindow();
TestGame game(glfwWindow, glm::vec3(0.2f, -1.5f, 0.0f), glm::vec3(-0.5f, 0.0f, 0.0f), "Test.unity");
TestGame Level2(glfwWindow, glm::vec3(0.2f, -1.5f, 0.0f), glm::vec3(-0.5f, 0.0f, 0.0f), "Lvl2.unity");

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
	Clumsy::EventSystem::GetInstance()->SendEvent("scroll");
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "Cursor Position at " << xpos << " : " << ypos << std::endl;
		mp.Update();		

		float screenX = 2.0f * xpos / SCR_WIDTH - 1.0f;
		float screenY = 1.0f - 2.0f * ypos / SCR_HEIGHT;

		if (Clumsy::RenderEngine::GetInstance()->GetStoreGUI()->IsEnabled())
		{
			Clumsy::RenderEngine::GetInstance()->GetStoreGUI()->HandleButtonClick(screenX, screenY);
		}
		else if (Clumsy::RenderEngine::GetInstance()->GetWarehouseGUI()->IsEnabled())
		{
			Clumsy::RenderEngine::GetInstance()->GetWarehouseGUI()->HandleButtonClick(screenX, screenY);
		}
		else if (Clumsy::RenderEngine::GetInstance()->GetMenuGUI()->IsEnabled()) 
		{
			Clumsy::RenderEngine::GetInstance()->GetMenuGUI()->HandleButtonClick(screenX, screenY, glfwWindow);
		}
		else if (Clumsy::RenderEngine::GetInstance()->GetCreditsGUI()->IsEnabled())
		{
			Clumsy::RenderEngine::GetInstance()->GetCreditsGUI()->HandleButtonClick(screenX, screenY);
		}
		else if (Clumsy::RenderEngine::GetInstance()->GetPokemonGUI()->IsEnabled()) 
		{
			Clumsy::RenderEngine::GetInstance()->GetPokemonGUI()->HandleButtonClick(screenX, screenY);
		}
		else
		{
			float screenX = 2.0f * xpos / SCR_WIDTH - 1.0f;
			float screenY = 1.0f - 2.0f * ypos / SCR_HEIGHT;

			glm::vec2 centerButton = Clumsy::RenderEngine::GetInstance()->GetCenterButton()->GetCorner();
			glm::vec2 endTurnButton = Clumsy::RenderEngine::GetInstance()->GetEndTurnButton()->GetCorner();
			glm::vec2 restartButton = Clumsy::RenderEngine::GetInstance()->GetRestartButton()->GetCorner();
			glm::vec2 scale1 = Clumsy::RenderEngine::GetInstance()->GetCenterButton()->GetScale();
			glm::vec2 scale2 = Clumsy::RenderEngine::GetInstance()->GetEndTurnButton()->GetScale();
			glm::vec2 scale3 = Clumsy::RenderEngine::GetInstance()->GetRestartButton()->GetScale();

			if (screenX > (centerButton.x - (scale1.x / 2)) && screenX < (centerButton.x + (scale1.x / 2))
				&& screenY < (centerButton.y + scale1.y) && screenY > centerButton.y)
			{
				//Clumsy::RenderEngine::GetInstance()->isPlayed = true;
				Clumsy::RenderEngine::GetInstance()->GetCenterButton()->OnClick();
				Clumsy::Player* player = dynamic_cast<Clumsy::Player*>(Clumsy::TurnSystem::GetInstance()->GetActivePlayer());
				if (player)
				{
					glm::vec3 position = player->m_Rmc->m_Transform.GetPos();
					Clumsy::RenderEngine::GetInstance()->getCamera()->MoveToPosition(position.x, position.z);
				}
			}
			else if (screenX > (endTurnButton.x - (scale2.x / 2)) && screenX < (endTurnButton.x + (scale2.x / 2))
				&& screenY < (endTurnButton.y + scale2.y) && screenY > endTurnButton.y)
			{
				Clumsy::RenderEngine::GetInstance()->GetEndTurnButton()->OnClick();
				Clumsy::Player* player = dynamic_cast<Clumsy::Player*>(Clumsy::TurnSystem::GetInstance()->GetActivePlayer());
				if (player)
					player->UseAllActions();
			}
			else if (screenX > (restartButton.x - (scale3.x / 2)) && screenX < (restartButton.x + (scale3.x / 2))
				&& screenY < (restartButton.y + scale3.y) && screenY > restartButton.y)
			{
				Clumsy::RenderEngine::GetInstance()->GetRestartButton()->OnClick();
				Clumsy::RenderEngine::GetInstance()->SetBurntToZero();
				Clumsy::TurnSystem::GetInstance()->SetTurnCounter(0);
				Clumsy::RenderEngine::GetInstance()->enemy->SetIsDead(true);
				if (Clumsy::RenderEngine::GetInstance()->GetFirstLevel())
				{
					game.getRoot().DeleteAll();
					game.Init();
				}
				else
				{
					Level2.getRoot().DeleteAll();
					Level2.Init();
				}
				Clumsy::RenderEngine::GetInstance()->m_Cubes.clear();
				Clumsy::TurnSystem::GetInstance()->DeletePlayers();
				Clumsy::PhysicsEngine::GetInstance()->m_Objects.clear();
				Clumsy::RenderEngine::GetInstance()->treeTransforms.clear();
				Clumsy::RenderEngine::GetInstance()->cutTreesTransforms.clear();
				Clumsy::RenderEngine::GetInstance()->ground.clear();
				Clumsy::RenderEngine::GetInstance()->groundBurned.clear();
				Clumsy::RenderEngine::GetInstance()->groundSand.clear();
			}
			else
			{
				Clumsy::RenderEngine::GetInstance()->SetShakeTime(0.2f);
				Clumsy::RenderEngine::GetInstance()->GetPostProcessor()->m_Shake = true;

				// movement
				Clumsy::GameObject* player = Clumsy::TurnSystem::GetInstance()->GetActivePlayer();
				Clumsy::EventSystem::GetInstance()->SendEvent("move", (void*)player);
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	Clumsy::RenderEngine::CreateInstance(glfwWindow, window, camera);
	Clumsy::EventSystem::GetInstance()->SubscribeListener("scroll", Clumsy::AudioMaster::GetInstance());
	Clumsy::EventSystem::GetInstance()->SubscribeListener("move", &mp);
	Clumsy::EventSystem::GetInstance()->SubscribeListener("hire", &game);

	glfwSetScrollCallback(glfwWindow, scroll_callback);
	glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);

	Clumsy::CoreEngine coreEngine(60.0f, window, &game, &Level2);

	std::cout << game.getRoot().GetAllChildren().size() << std::endl;
	Clumsy::EventSystem::GetInstance()->SubscribeListener("Level2", &coreEngine);


	coreEngine.Start();



	window->~Window();
	Clumsy::AudioMaster::GetInstance()->Drop();
	return 0;
}