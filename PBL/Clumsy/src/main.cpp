
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>
#include "glm/gtx/string_cast.hpp"

#include "Clumsy.h"
//#include "../src/Core/Game.h"



class TestGame : public Clumsy::Game {
public:
	TestGame(GLFWwindow* window) : m_GLFWWindow(window) {
	
	};
	
	virtual void Move() {
		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			//object1->SetTranfsorm(Clumsy::Transform transform())
			//object1.GetTransform().GetPos().x -= 2.0f;
			//object1->SetTranfsorm();//-= glm::vec3(-2.0f, 0.0f, 0.0f);
			//object1->GetTransform().SetPos(object1->GetTransform().GetPos() - glm::vec3(-2.0f, 0.0f, 0.0f));
			
			std::cout << "lewo" << std::endl;
			//std::cout << glm::to_string(object1->GetTransform().GetPos()) << std::endl;
			//object.GetTransform().GetPos() -= 2.0f;
		}
	}
	
	virtual void Init() {
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::quat rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		float scale = 0.2f;
		Clumsy::Transform transform(pos, rot, scale);

		Clumsy::Transform transform2(pos + 0.5f, rot, 0.1f);

		Clumsy::Model m1("../Clumsy/src/models/capsule.obj");

		//	AddToScene((new Clumsy::GameObject(transform))->AddComponent(new Clumsy::RenderModelComponent(m1, transform)));

		//	AddToScene((new Clumsy::GameObject(transform2))->AddComponent(new Clumsy::RenderModelComponent(m1, transform2))
		//		->AddComponent(new Clumsy::PhysicsObjectComponent(new Clumsy::PhysicsObject(new Clumsy::BoundingSphere(transform2.GetPos(), 1.0f)))));

		Clumsy::PhysicsEngine physicsEngine;
		
		Clumsy::GameObject* object1 = new Clumsy::GameObject(transform);
		Clumsy::GameObject* object2 = new Clumsy::GameObject(transform2);

		physicsEngine.AddObject(Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(object1->GetTransform().GetPos(), 0.1f)));
		physicsEngine.AddObject(Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(object2->GetTransform().GetPos(), 0.1f)));
		
		Clumsy::PhysicsEngineComponent* physicsEngineComponent
			= new Clumsy::PhysicsEngineComponent(physicsEngine);

		//if (glfwGetKey(m_GLFWWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
		//{
		//	object1->GetTransform().SetPos(object1->GetTransform().GetPos() - 2.0f);
		//	std::cout << "lewo" << std::endl;
		//	//object.GetTransform().GetPos() -= 2.0f;
		//}
		
		AddToScene((object1)->AddComponent(new Clumsy::RenderModelComponent(m1, object1->GetTransform())));
		AddToScene((object2)->AddComponent(new Clumsy::RenderModelComponent(m1, object2->GetTransform())));

	for (unsigned int i = 0; i < physicsEngineComponent->GetPhysicsEngine().GetNumObjects(); i++)
	{
		object1->AddComponent(new Clumsy::PhysicsObjectComponent(&physicsEngineComponent->GetPhysicsEngine().GetObject(i)));
		object2->AddComponent(new Clumsy::PhysicsObjectComponent(&physicsEngineComponent->GetPhysicsEngine().GetObject(i)));
	}

		AddToScene((new Clumsy::GameObject())
			->AddComponent(physicsEngineComponent));

		std::cout << "Init gierki" << std::endl;
	}

private:
	GLFWwindow* m_GLFWWindow;
	
};



const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Clumsy::Camera* camera = new Clumsy::Camera(glm::vec3(0.0f, 0.0f, 3.0f));

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

int main() 
{
	Clumsy::Window* window = new Clumsy::Window(SCR_WIDTH, SCR_HEIGHT);
	GLFWwindow* glfwWindow = window->GetGLFWWindow();

	Clumsy::RenderEngine* renderEngine = new Clumsy::RenderEngine(glfwWindow, window, camera);
	glfwSetScrollCallback(glfwWindow, scroll_callback);

	Clumsy::PhysicsEngine* physicsEngine = new Clumsy::PhysicsEngine();

	//Clumsy::Game* game = new Clumsy::Game();
	TestGame game(glfwWindow);
	
	Clumsy::CoreEngine coreEngine(60.0f, window, renderEngine, &game, physicsEngine);

	std::cout << game.getRoot().GetAllChildren().size() << std::endl;
	
	//std::cout << game.getRoot().GetAllChildren()[1]->GetComponents().size() << std::endl;
	coreEngine.Start();
	//renderEngine->Start();
	window->~Window();
	return 0;
}