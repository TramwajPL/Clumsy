#pragma once

#include "../RenderEngine/Window.h"
#include "../RenderEngine/Camera.h"

namespace Clumsy
{
	class MousePicker
	{
	public:
		MousePicker(Window* window, Camera* camera) :
			m_Window(window),
			m_Camera(camera) {}

		void Update();
		glm::vec3 CalculateMouseRey();

	private:
		Window* m_Window;
		Camera* m_Camera;
	};
}