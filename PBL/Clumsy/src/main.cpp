
#include "pch.h"



#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Clumsy.h"


Clumsy::GameObject* object1;
Clumsy::GameObject* map = new Clumsy::GameObject();
Clumsy::RenderModelComponent* rmc;
Clumsy::GameObject* boy;
bool isScrolled = false;

Clumsy::AudioMaster* Clumsy::AudioMaster::m_Instance = 0;
Clumsy::EventSystem* Clumsy::EventSystem::m_Instance = 0;
Clumsy::PhysicsEngine* Clumsy::PhysicsEngine::m_Instance = 0;
Clumsy::RenderEngine* Clumsy::RenderEngine::m_Instance = 0;

class TestGame : public Clumsy::Game 
{
public:
	TestGame(GLFWwindow* window) : 
		m_GLFWWindow(window) {}
		
	virtual void Init() 
	{
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::quat rotBoy = glm::angleAxis(glm::radians(-180.f), glm::vec3(1.0f, 0.0f, 0.0f)); 

		float scale = 0.0001f;

		Clumsy::Transform boyTransform(pos + 0.5f, rotBoy, 0.1f);
		Clumsy::Transform boyTransform2(pos, rotBoy, 0.1f);

	
		Clumsy::Model* model = new Clumsy::Model();
		//m1->loadModel("../Clumsy/src/models/Dwarf/dwarf.X");
		model->loadModel("../Clumsy/src/models/man/model.dae");
		//model->loadModel("../Clumsy/src/models/capsule.obj");
		
		boy = new Clumsy::GameObject(boyTransform);
		Clumsy::GameObject* boy2 = new Clumsy::GameObject(boyTransform2);
		
		Clumsy::PhysicsObject* ob1 = new Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(boy->GetTransform().GetPos(), 0.1f), &boy->GetTransform());

		Clumsy::PhysicsObject* ob2 = new Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(boy2->GetTransform().GetPos(), 0.1f), &boy2->GetTransform());

		Clumsy::PhysicsEngine::GetInstance()->AddObject(*ob1);
		Clumsy::PhysicsEngine::GetInstance()->AddObject(*ob2);

		Clumsy::PhysicsEngineComponent* physicsEngineComponent
			= new Clumsy::PhysicsEngineComponent();
		rmc = new Clumsy::RenderModelComponent(model, boy->GetTransform());
		AddToScene((boy)->AddComponent(rmc));
		AddToScene((boy2)->AddComponent(new Clumsy::RenderModelComponent(model, boy2->GetTransform())));

		boy->AddComponent(new Clumsy::PhysicsObjectComponent(ob1));
		boy2->AddComponent(new Clumsy::PhysicsObjectComponent(ob2));

		AddToScene((new Clumsy::GameObject())
			->AddComponent(physicsEngineComponent));

		SceneParser(map);
		/*
		std::cout << "Init gierki" << std::endl;
		std::cout <<"BOY 1 POSITION: " << glm::to_string(boy->GetTransform().GetPos()) << std::endl;
		std::cout <<"BOY 2 POSITION: "<< glm::to_string(boy2->GetTransform().GetPos()) << std::endl;*/

		//Clumsy::AudioMaster::GetInstance()->PlayAmbientMusic();
	}

private:
	GLFWwindow* m_GLFWWindow;	
};

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;//zmieniæ

Clumsy::Camera* camera = new Clumsy::Camera(glm::vec3(0.0f, 13.0f, -8.0f));

Clumsy::Window* window = new Clumsy::Window(SCR_WIDTH, SCR_HEIGHT);

glm::mat4 projectionMP = glm::perspective(glm::radians(camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);

Clumsy::MousePicker mp(camera, window, projectionMP);

glm::vec3 v1 = glm::vec3(0.0f, 0.0f, -2.0f) - glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 v2 = glm::vec3(0.0f, 0.0f, -2.0f) + glm::vec3(1.0f, 1.0f, 1.0f);

Clumsy::Aabb a1(v1, v2);


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
	//isScrolled = true;
	//Clumsy::AudioMaster::GetInstance()->PlayBell();
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

		if (xpos > 25.0 && xpos < 165.0 && ypos > 145.0 && ypos < 180.0)
		{
			Clumsy::RenderEngine::GetInstance()->GetCenterButton()->OnClick();
		}
		else if (xpos > 25.0 && xpos < 165.0 && ypos > 195.0 && ypos < 240.0)
		{
			Clumsy::RenderEngine::GetInstance()->GetEndTurnButton()->OnClick();
		}
		/*float x = -0.9f;
		float y = 0.65f;

		float num = (1 + x) * SCR_WIDTH * 0.15;
		std::cout << "x calc " << num <<  std::endl;

		if (xpos > (1 + Clumsy::RenderEngine::GetInstance()->GetCenterButton()->GetCorner().x) * SCR_WIDTH * 0.15 && 
			xpos < Clumsy::RenderEngine::GetInstance()->GetCenterButton()->GetCorner().x + SCR_WIDTH * Clumsy::RenderEngine::GetInstance()->GetCenterButton()->GetScale().x * 5 && 
			ypos > Clumsy::RenderEngine::GetInstance()->GetCenterButton()->GetCorner().y * SCR_HEIGHT * 0.25 &&
			ypos < Clumsy::RenderEngine::GetInstance()->GetCenterButton()->GetCorner().y + SCR_HEIGHT * Clumsy::RenderEngine::GetInstance()->GetCenterButton()->GetScale().y * 5)
		{
			Clumsy::RenderEngine::GetInstance()->GetCenterButton()->OnClick();
		}
		else if (xpos > 20.0 && xpos < 170.0 && ypos > 195.0 && ypos < 235.0)
		{
			Clumsy::RenderEngine::GetInstance()->GetEndTurnButton()->OnClick();
		}*/

		glm::vec3 vec3 = mp.GetPickedObject();
		rmc->m_Transform.SetPos(vec3);

	}
}
int main() 
{
	GLFWwindow* glfwWindow = window->GetGLFWWindow();

	Clumsy::RenderEngine::CreateInstance(glfwWindow, window, camera);
	Clumsy::EventSystem::GetInstance()->SubscribeListener("scroll", Clumsy::AudioMaster::GetInstance());
	
	glfwSetScrollCallback(glfwWindow, scroll_callback);
	glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);

	TestGame game(glfwWindow);
	
	Clumsy::CoreEngine coreEngine(60.0f, window, &game);

	std::cout << game.getRoot().GetAllChildren().size() << std::endl;
	
	coreEngine.Start();
	window->~Window();
	Clumsy::AudioMaster::GetInstance()->Drop();
	return 0;
}