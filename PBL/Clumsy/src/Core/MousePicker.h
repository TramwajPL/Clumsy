#pragma once

#include <glm/glm.hpp>

#include "../RenderEngine/Window.h"
#include "../RenderEngine/Camera.h"
#include "../PhysicsEngine/Aabb.h"
#include "../Core/GameObject.h"
#include "../Components/PhysicsObjectComponent.h"
#include "../PhysicsEngine/PhysicsEngine.h"


namespace Clumsy
{
	class MousePicker
	{
	public:
		MousePicker(Camera* camera, Window* window, glm::mat4 projectionMatrix) :
			m_Camera(camera),
			m_Window(window),
			m_ProjectionMatrix(projectionMatrix),
			m_ViewMatrix(camera->GetViewMatrix()) {}

		glm::vec3 GetCurrentRay() { return m_CurrentRay; }
		void Update();
		glm::vec3 CalculateMouseRey();
		glm::vec3 ToWorldCoords(glm::vec4 eyeCoords);
		glm::vec4 ToEyeCoords(glm::vec4 clipCoords);
		glm::vec2 GetNormalisedDeviceCoordinates(float mouseX, float mouseY);

		float CheckCollision(const Collider* aabb);

		glm::vec3 GetPickedObject(PhysicsEngine* physicsEngine);

	private:
		glm::vec3 m_CurrentRay;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		Window* m_Window;
		Camera* m_Camera;
	};
}