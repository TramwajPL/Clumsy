
#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Clumsy.h"

Clumsy::Transform transform;
Clumsy::GameObject* object1;
Clumsy::GameObject* map = new Clumsy::GameObject();
Clumsy::PhysicsEngine physicsEngine;
Clumsy::RenderModelComponent* rmc;

class TestGame : public Clumsy::Game 
{
public:


	virtual void Init() {
	TestGame(GLFWwindow* window) : 
		m_GLFWWindow(window) {}
		
	virtual void Init() 
	{
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 pos4 = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::quat rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		glm::quat rot2 = glm::angleAxis(glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::vec3 pos2 = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 pos3 = glm::vec3(0.0f, 1.0f, 0.0f);

		float scale = 0.2f;

		transform.SetPos(pos);
		transform.SetRot(rot);
		transform.SetScale(scale); 
		Clumsy::Transform transform2(pos + 0.5f, rot, 0.1f);

		Clumsy::Model m1("../Clumsy/src/models/capsule.obj");


		AddToScene((new Clumsy::GameObject(transform))->AddComponent(new Clumsy::RenderModelComponent(m1, transform)));

		AddToScene((new Clumsy::GameObject(transform2))->AddComponent(new Clumsy::RenderModelComponent(m1, transform2)));


=======
	
		Clumsy::Model m1("../Clumsy/res/models/capsule.obj");
		Clumsy::Model* m2 = new Clumsy::Model("../Clumsy/res/models/jazda.obj");
		
		object1 = new Clumsy::GameObject(transform);
		Clumsy::GameObject* object2 = new Clumsy::GameObject(transform2);
		
		Clumsy::PhysicsObject* ob1 = new Clumsy::PhysicsObject(
			new Clumsy::BoundingSphere(object2->GetTransform().GetPos(), 0.1f), &object2->GetTransform());

		physicsEngine.AddObject(*ob1);

		Clumsy::PhysicsEngineComponent* physicsEngineComponent
			= new Clumsy::PhysicsEngineComponent(physicsEngine);
		
		rmc = new  Clumsy::RenderModelComponent(m1, object1->GetTransform());
		AddToScene((object1)->AddComponent(rmc));
		AddToScene((object2)->AddComponent(new Clumsy::RenderModelComponent(m1, object2->GetTransform())));

		object1->AddComponent(new Clumsy::PhysicsObjectComponent(ob1));

		AddToScene((new Clumsy::GameObject())
			->AddComponent(physicsEngineComponent));

		SceneParser(&physicsEngine, map);
>>>>>>> development
		std::cout << "Init gierki" << std::endl;
		std::cout << glm::to_string(object1->GetTransform().GetPos()) << std::endl;
		std::cout << glm::to_string(object2->GetTransform().GetPos()) << std::endl;
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
		object1->SetPos(vec3);
		rmc->m_Transform.SetPos(vec3);
		std::cout << "trans " << glm::to_string(rmc->m_Transform.GetPos()) << std::endl;
		std::cout << " zamieniony " << glm::to_string(object1->GetTransform().GetPos());
		std::cout << " parent? " << object1->GetComponents().size() << std::endl;
	}
}

int main() 
{
	GLFWwindow* glfwWindow = window->GetGLFWWindow();

	Clumsy::RenderEngine* renderEngine = new Clumsy::RenderEngine(glfwWindow, window, camera);
	glfwSetScrollCallback(glfwWindow, scroll_callback);
	
	glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);

	//Clumsy::Game* game = new Clumsy::Game();
	TestGame game;

	Clumsy::DirectionalLight* dl = new Clumsy::DirectionalLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1, 1, 1), 0.8f);

	game.AddToScene((new Clumsy::GameObject(Clumsy::Transform()))
		->AddComponent(dl));

	Clumsy::CoreEngine coreEngine(60.0f, window, renderEngine, &game);
	Clumsy::PhysicsEngine* physicsEngine = new Clumsy::PhysicsEngine();

	TestGame game(glfwWindow);
	
	Clumsy::CoreEngine coreEngine(60.0f, window, renderEngine, &game, physicsEngine);

	dl->AddToEngine(new Clumsy::CoreEngine(coreEngine));


	std::cout << game.getRoot().GetAllChildren().size() << std::endl;
	
	coreEngine.Start();

	window->~Window();
	return 0;
}