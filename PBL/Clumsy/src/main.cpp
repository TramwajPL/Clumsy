
#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Clumsy.h"


Clumsy::GameObject* object1;
Clumsy::GameObject* map = new Clumsy::GameObject();
Clumsy::PhysicsEngine physicsEngine;
Clumsy::RenderModelComponent* rmc;
Clumsy::GameObject* boy;

Clumsy::AudioMaster* Clumsy::AudioMaster::m_Instance = 0;

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
		
		boy = new Clumsy::GameObject(boyTransform);
		Clumsy::GameObject* boy2 = new Clumsy::GameObject(boyTransform2);
		
		Clumsy::PhysicsObject* ob1 = new Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(boy->GetTransform().GetPos(), 0.1f), &boy->GetTransform());

		Clumsy::PhysicsObject* ob2 = new Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(boy2->GetTransform().GetPos(), 0.1f), &boy2->GetTransform());

		physicsEngine.AddObject(*ob1);
		physicsEngine.AddObject(*ob2);

		Clumsy::PhysicsEngineComponent* physicsEngineComponent
			= new Clumsy::PhysicsEngineComponent(physicsEngine);
		rmc = new Clumsy::RenderModelComponent(model, boy->GetTransform());
		AddToScene((boy)->AddComponent(rmc));
		AddToScene((boy2)->AddComponent(new Clumsy::RenderModelComponent(model, boy2->GetTransform())));

		boy->AddComponent(new Clumsy::PhysicsObjectComponent(ob1));
		boy2->AddComponent(new Clumsy::PhysicsObjectComponent(ob2));

		AddToScene((new Clumsy::GameObject())
			->AddComponent(physicsEngineComponent));

		SceneParser(&physicsEngine, map);
		std::cout << "Init gierki" << std::endl;
		std::cout <<"BOY 1 POSITION: " << glm::to_string(boy->GetTransform().GetPos()) << std::endl;
		std::cout <<"BOY 2 POSITION: "<< glm::to_string(boy2->GetTransform().GetPos()) << std::endl;

		//Clumsy::AudioMaster::GetInstance()->PlayAmbientMusic();
	}

private:
	GLFWwindow* m_GLFWWindow;	
};



const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Clumsy::Camera* camera = new Clumsy::Camera(glm::vec3(0.0f, 13.0f, -8.0f));

Clumsy::Window* window = new Clumsy::Window(SCR_WIDTH, SCR_HEIGHT);

glm::mat4 projectionMP = glm::perspective(glm::radians(camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

Clumsy::MousePicker mp(camera, window, projectionMP);

glm::vec3 v1 = glm::vec3(0.0f, 0.0f, -2.0f) - glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 v2 = glm::vec3(0.0f, 0.0f, -2.0f) + glm::vec3(1.0f, 1.0f, 1.0f);

Clumsy::Aabb a1(v1, v2);


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);

	Clumsy::AudioMaster::GetInstance()->PlayBell();
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

		std::cout << "RAY: " << mp.GetCurrentRay().x << " , " << mp.GetCurrentRay().y << " , " << mp.GetCurrentRay().z << std::endl;

		glm::vec3 vec3 = mp.GetPickedObject(&physicsEngine);
		std::cout << glm::to_string(vec3) << std::endl;
		//object1->SetPos(vec3);
		rmc->m_Transform.SetPos(vec3);
		std::cout << "boiii " << glm::to_string(boy->GetTransform().GetPos()) << std::endl;
		//boy->m_Transform.SetPos(vec3);
		//std::cout << "trans " << glm::to_string(rmc->m_Transform.GetPos()) << std::endl;
		//std::cout << " zamieniony " << glm::to_string(object1->GetTransform().GetPos());
		//std::cout << " parent? " << object1->GetComponents().size() << std::endl;
	}
}
int main() 
{
	GLFWwindow* glfwWindow = window->GetGLFWWindow();

	Clumsy::RenderEngine* renderEngine = new Clumsy::RenderEngine(glfwWindow, window, camera);
	glfwSetScrollCallback(glfwWindow, scroll_callback);
	
	glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);

	Clumsy::PhysicsEngine* physicsEngine = new Clumsy::PhysicsEngine();

	TestGame game(glfwWindow);
	
	Clumsy::CoreEngine coreEngine(60.0f, window, renderEngine, &game, physicsEngine);

	std::cout << game.getRoot().GetAllChildren().size() << std::endl;
	
	coreEngine.Start();
	window->~Window();
	Clumsy::AudioMaster::GetInstance()->Drop();
	return 0;
}