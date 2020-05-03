
#include "../pch.h"

#include "MousePicker.h"

namespace Clumsy
{
	void MousePicker::Update()
	{
		m_ViewMatrix = m_Camera->GetViewMatrix();
		m_CurrentRay = CalculateMouseRey();
	}

	glm::vec3 MousePicker::CalculateMouseRey()
	{
		double xpos, ypos;
		glfwGetCursorPos(m_Window->GetGLFWWindow(), &xpos, &ypos);
		glm::vec2 normalizedCoords = GetNormalisedDeviceCoordinates(xpos, ypos);
		glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
		glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
		glm::vec3 worldRay = ToWorldCoords(eyeCoords);
		return worldRay;
	}

	glm::vec3 MousePicker::ToWorldCoords(glm::vec4 eyeCoords)
	{
		glm::mat4 invertedView = glm::inverse(m_ViewMatrix);
		glm::vec4 rayWorld = invertedView * eyeCoords;
		glm::vec3 mouseRay = glm::normalize(glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z));
		return mouseRay;
	}

	glm::vec4 MousePicker::ToEyeCoords(glm::vec4 clipCoords)
	{
		glm::mat4 invertedProjection = glm::inverse(m_ProjectionMatrix);
		glm::vec4 eyeCoords = invertedProjection * clipCoords;
		return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
	}

	glm::vec2 MousePicker::GetNormalisedDeviceCoordinates(float mouseX, float mouseY)
	{
		float x = (2.0f * mouseX) / m_Window->GetWidth() - 1;
		float y = (2.0f * mouseY) / m_Window->GetHeight() - 1;
		return glm::vec2(x, -y);
	}
}