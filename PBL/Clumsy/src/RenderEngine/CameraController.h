#pragma once

#include "Camera.h"
#include "../Core/Timestep.h"

namespace Clumsy {

	class CameraController
	{
	public:
		CameraController(float aspectRatio, bool rotation);

		void OnUpdate(Timestep ts);
		//void OnEvent(Event& e);

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		//bool OnMouseScrolled(MouseScrolledEvent& e);
		//bool OnWindowResized(WindowResizeEvent& e);
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		Camera m_Camera;

		bool m_Rotation = false;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 180.0f;
	};
}