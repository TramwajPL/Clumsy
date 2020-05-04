
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

#include "Clumsy.h"
//#include "../src/Core/Game.h"



class TestGame : public Clumsy::Game {
public:
	virtual void Init() {
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::quat rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		float scale = 0.2f;
		Clumsy::Transform transform(pos, rot, scale);

		Clumsy::Transform transform2(pos + 0.5f, rot, 0.1f);

		Clumsy::Model m1("../Clumsy/src/models/capsule.obj");

		AddToScene((new Clumsy::GameObject(transform))->AddComponent(new Clumsy::RenderModelComponent(m1, transform)));

		AddToScene((new Clumsy::GameObject(transform2))->AddComponent(new Clumsy::RenderModelComponent(m1, transform2)));

		Clumsy::Parser::SceneParser("../Clumsy/src/SampleScene.unity");

		std::cout << "Init gierki" << std::endl;
	}
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

	//Clumsy::Game* game = new Clumsy::Game();
	TestGame game;
	
	Clumsy::CoreEngine coreEngine(60.0f, window, renderEngine, &game);

	std::cout << game.getRoot().GetAllChildren().size() << std::endl;
	coreEngine.Start();
	//renderEngine->Start();
	window->~Window();
	return 0;
}