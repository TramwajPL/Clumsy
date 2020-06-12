#include "pch.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Clumsy.h"

const unsigned int SCR_WIDTH = 1920;
//const unsigned int SCR_WIDTH = 1366;
//const unsigned int SCR_HEIGHT = 768;//zmieniæ
const unsigned int SCR_HEIGHT = 1080;//zmieniæ

Clumsy::GameObject* object1;
Clumsy::RenderModelComponent* rmc;
Clumsy::GameObject* boy;
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
	TestGame(GLFWwindow* window) :
		m_GLFWWindow(window) {}

	virtual void Init()
	{
		std::string filename = "Test.unity";
		SceneParser(Clumsy::RenderEngine::GetInstance()->map, filename);

		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::quat rotBoy = glm::angleAxis(glm::radians(-180.f), glm::vec3(1.0f, 0.0f, 0.0f));

		float scale = 0.0001f;

		Clumsy::Transform boyTransform(pos + 0.5f, rotBoy, 0.1f);
		Clumsy::Transform boyTransform2(pos, rotBoy, 0.1f);


		Clumsy::Model* model = new Clumsy::Model();
		model->loadModel("../Clumsy/src/models/man/model.dae");

		boy = new Clumsy::Player(boyTransform);
		Clumsy::Player* boy2 = new Clumsy::Player(boyTransform2);

		Clumsy::PhysicsObject* ob1 = new Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(boy->GetTransform().GetPos(), 0.1f), &boy->GetTransform());

		Clumsy::PhysicsObject* ob2 = new Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(boy2->GetTransform().GetPos(), 0.1f), &boy2->GetTransform());

		Clumsy::PhysicsEngine::GetInstance()->AddObject(*ob1);
		Clumsy::PhysicsEngine::GetInstance()->AddObject(*ob2);

		Clumsy::PhysicsEngineComponent* physicsEngineComponent
			= new Clumsy::PhysicsEngineComponent();
		rmc = new Clumsy::RenderModelComponent(model, boy->GetTransform(), 90.0f);

		Clumsy::RenderModelComponent* rmc1 = new Clumsy::RenderModelComponent(model, boy->GetTransform(), 90.0f);
		boy->m_Rmc = rmc1;
		AddToScene((boy)->AddComponent(rmc1));

		Clumsy::RenderModelComponent* rmc2 = new Clumsy::RenderModelComponent(model, boy2->GetTransform(), 90.0f);
		boy2->m_Rmc = rmc2;
		AddToScene((boy2)->AddComponent(rmc2));

		boy->AddComponent(new Clumsy::PhysicsObjectComponent(ob1));
		boy2->AddComponent(new Clumsy::PhysicsObjectComponent(ob2));

		AddToScene((new Clumsy::GameObject())
			->AddComponent(physicsEngineComponent));

		Clumsy::Nature* nature = new Clumsy::Nature();

		Clumsy::TurnSystem::GetInstance()->AddPlayer(nature);
		Clumsy::TurnSystem::GetInstance()->AddPlayer(boy);
		Clumsy::TurnSystem::GetInstance()->AddPlayer(boy2);

		//Clumsy::AudioMaster::GetInstance()->PlayAmbientMusic();
	}

private:
	GLFWwindow* m_GLFWWindow;
};


Clumsy::Camera* camera = new Clumsy::Camera(glm::vec3(0.0f, 13.0f, -8.0f));

Clumsy::Window* window = new Clumsy::Window(SCR_WIDTH, SCR_HEIGHT);

glm::mat4 projectionMP = glm::perspective(glm::radians(camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);

Clumsy::MousePicker mp(camera, window, projectionMP);

glm::vec3 v1 = glm::vec3(0.0f, 0.0f, -2.0f) - glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 v2 = glm::vec3(0.0f, 0.0f, -2.0f) + glm::vec3(1.0f, 1.0f, 1.0f);

Clumsy::Aabb a1(v1, v2);

GLFWwindow* glfwWindow = window->GetGLFWWindow();
TestGame game(glfwWindow);

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
				Clumsy::RenderEngine::GetInstance()->GetCenterButton()->OnClick();
				std::cout << "Is played: " << Clumsy::RenderEngine::GetInstance()->isPlayed << std::endl;
			}
			else if (screenX > (endTurnButton.x - (scale2.x / 2)) && screenX < (endTurnButton.x + (scale2.x / 2))
				&& screenY < (endTurnButton.y + scale2.y) && screenY > endTurnButton.y)
			{
				Clumsy::RenderEngine::GetInstance()->GetEndTurnButton()->OnClick();
				Clumsy::RenderEngine::GetInstance()->isPlayed = true;
			}
			else if (screenX > (restartButton.x - (scale3.x / 2)) && screenX < (restartButton.x + (scale3.x / 2))
				&& screenY < (restartButton.y + scale3.y) && screenY > restartButton.y)
			{
				Clumsy::RenderEngine::GetInstance()->GetRestartButton()->OnClick();
				Clumsy::RenderEngine::GetInstance()->isPlayed = false;
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
	Clumsy::RenderEngine::CreateInstance(glfwWindow, window, camera);
	Clumsy::EventSystem::GetInstance()->SubscribeListener("scroll", Clumsy::AudioMaster::GetInstance());
	Clumsy::EventSystem::GetInstance()->SubscribeListener("move", &mp);

	glfwSetScrollCallback(glfwWindow, scroll_callback);
	glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);

	Clumsy::CoreEngine coreEngine(60.0f, window, &game);

	std::cout << game.getRoot().GetAllChildren().size() << std::endl;

	coreEngine.Start();
	window->~Window();
	Clumsy::AudioMaster::GetInstance()->Drop();
	return 0;
}