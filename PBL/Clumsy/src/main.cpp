
#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>
#include "glm/gtx/string_cast.hpp"

#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>

#include "Clumsy.h"
//#include "../src/Core/Game.h"



class TestGame : public Clumsy::Game {
public:
	TestGame(GLFWwindow* window) : m_GLFWWindow(window) {
	
	};
		
	virtual void Init() {
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 pos4 = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::quat rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		glm::quat rot2 = glm::angleAxis(glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::vec3 pos2 = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 pos3 = glm::vec3(0.0f, 1.0f, 0.0f);

		float scale = 0.2f;
		Clumsy::Transform transform(pos, rot, scale);
		
		Clumsy::Transform transform2(pos + 0.5f, rot, 0.1f);

	
		Clumsy::Model m1("../Clumsy/src/models/capsule.obj");
		Clumsy::Model* m2 = new Clumsy::Model("../Clumsy/src/models/jazda.obj");

		Clumsy::PhysicsEngine physicsEngine;
		
		Clumsy::GameObject* object1 = new Clumsy::GameObject(transform);
		Clumsy::GameObject* object2 = new Clumsy::GameObject(transform2);


		physicsEngine.AddObject(Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(object1->GetTransform().GetPos(), 0.1f)));

		physicsEngine.AddObject(Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(object2->GetTransform().GetPos(), 0.1f)));
		
		Clumsy::PhysicsEngineComponent* physicsEngineComponent
			= new Clumsy::PhysicsEngineComponent(physicsEngine);
		
		object1->AddComponent(new Clumsy::MoveComponent());

		AddToScene((object1)->AddComponent(new Clumsy::RenderModelComponent(m1, object1->GetTransform())));
		AddToScene((object2)->AddComponent(new Clumsy::RenderModelComponent(m1, object2->GetTransform())));

	for (unsigned int i = 0; i < physicsEngineComponent->GetPhysicsEngine().GetNumObjects(); i++)
	{
		object1->AddComponent(new Clumsy::PhysicsObjectComponent(&physicsEngineComponent->GetPhysicsEngine().GetObject(i)));
		object2->AddComponent(new Clumsy::PhysicsObjectComponent(&physicsEngineComponent->GetPhysicsEngine().GetObject(i)));
	}

		AddToScene((new Clumsy::GameObject())
			->AddComponent(physicsEngineComponent));

		SceneParser();
		std::cout << "Init gierki" << std::endl;
		std::cout << glm::to_string(object1->GetTransform().GetPos()) << std::endl;
		std::cout << glm::to_string(object2->GetTransform().GetPos()) << std::endl;


	}

private:
	GLFWwindow* m_GLFWWindow;
	
};



const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Clumsy::Camera* camera = new Clumsy::Camera(glm::vec3(0.0f, -5.0f, 3.0f));

Clumsy::Window* window = new Clumsy::Window(SCR_WIDTH, SCR_HEIGHT);

glm::mat4 projectionMP = glm::perspective(glm::radians(camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

Clumsy::MousePicker mp(camera, window, projectionMP);

glm::vec3 v1 = glm::vec3(0.0f, 0.0f, -2.0f) - glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 v2 = glm::vec3(0.0f, 0.0f, -2.0f) + glm::vec3(1.0f, 1.0f, 1.0f);

Clumsy::Aabb a1(v1, v2);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
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

		std::cout << mp.CheckCollision(a1) << std::endl;
	}
}

int main() 
{
	GLFWwindow* glfwWindow = window->GetGLFWWindow();

	Clumsy::RenderEngine* renderEngine = new Clumsy::RenderEngine(glfwWindow, window, camera);
	glfwSetScrollCallback(glfwWindow, scroll_callback);
	glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);

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