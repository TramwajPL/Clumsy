
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

#include "Clumsy.h"
//#include "../src/Core/Game.h"



class TestGame : public Clumsy::Game {
public:
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
		pos += pos2;
		Clumsy::Transform transform3(pos, rot2, 0.0001f);
		pos += pos2;
		Clumsy::Transform transform4(pos, rot2, 0.0001f);
		pos += pos2;
		Clumsy::Transform transform5(pos, rot2, 0.0001f);
		pos += pos2;
		Clumsy::Transform transform6(pos, rot2, 0.0001f);
		pos += pos2;
		Clumsy::Transform transform7(pos, rot2, 0.0001f);
		pos += pos2;
		Clumsy::Transform transform8(pos, rot2, 0.0001f);
		pos += pos2;
		Clumsy::Transform transform9(pos, rot2, 0.0001f);
		pos4 += pos3;
		pos4 += pos2;
		Clumsy::Transform transform10(pos4, rot2, 0.0001f);
		pos4 += pos2;
		Clumsy::Transform transform11(pos4, rot2, 0.0001f);
		pos4 += pos2;
		Clumsy::Transform transform12(pos4, rot2, 0.0001f);
		pos4 += pos2;
		Clumsy::Transform transform13(pos4, rot2, 0.0001f);
		pos4 += pos2;
		Clumsy::Transform transform14(pos4, rot2, 0.0001f);
		pos4 += pos2;
		Clumsy::Transform transform15(pos4, rot2, 0.0001f);
		pos4 += pos2;
		Clumsy::Transform transform16(pos4, rot2, 0.0001f);

		Clumsy::Model m1("../Clumsy/src/models/capsule.obj");
		Clumsy::Model m2("../Clumsy/src/models/jazda.obj");

		AddToScene((new Clumsy::GameObject(transform))->AddComponent(new Clumsy::RenderModelComponent(m1, transform)));

		AddToScene((new Clumsy::GameObject(transform2))->AddComponent(new Clumsy::RenderModelComponent(m1, transform2)));

		AddToScene((new Clumsy::GameObject(transform3))->AddComponent(new Clumsy::RenderModelComponent(m2, transform3)));
		AddToScene((new Clumsy::GameObject(transform4))->AddComponent(new Clumsy::RenderModelComponent(m2, transform4)));
		AddToScene((new Clumsy::GameObject(transform5))->AddComponent(new Clumsy::RenderModelComponent(m2, transform5)));
		AddToScene((new Clumsy::GameObject(transform6))->AddComponent(new Clumsy::RenderModelComponent(m2, transform6)));
		AddToScene((new Clumsy::GameObject(transform7))->AddComponent(new Clumsy::RenderModelComponent(m2, transform7)));
		AddToScene((new Clumsy::GameObject(transform8))->AddComponent(new Clumsy::RenderModelComponent(m2, transform8)));
		AddToScene((new Clumsy::GameObject(transform9))->AddComponent(new Clumsy::RenderModelComponent(m2, transform9)));
		AddToScene((new Clumsy::GameObject(transform10))->AddComponent(new Clumsy::RenderModelComponent(m2, transform10)));
		AddToScene((new Clumsy::GameObject(transform11))->AddComponent(new Clumsy::RenderModelComponent(m2, transform11)));
		AddToScene((new Clumsy::GameObject(transform12))->AddComponent(new Clumsy::RenderModelComponent(m2, transform12)));
		AddToScene((new Clumsy::GameObject(transform13))->AddComponent(new Clumsy::RenderModelComponent(m2, transform13)));
		AddToScene((new Clumsy::GameObject(transform14))->AddComponent(new Clumsy::RenderModelComponent(m2, transform14)));
		AddToScene((new Clumsy::GameObject(transform15))->AddComponent(new Clumsy::RenderModelComponent(m2, transform15)));
		AddToScene((new Clumsy::GameObject(transform16))->AddComponent(new Clumsy::RenderModelComponent(m2, transform16)));


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