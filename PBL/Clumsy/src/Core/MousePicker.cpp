
#include "../pch.h"

#include <glm/gtx/string_cast.hpp>

#include "MousePicker.h"
#include "../Components/RenderModelComponent.h"

namespace Clumsy
{
	template<typename Base, typename T>
	inline bool instanceof(const T*) {
		return std::is_base_of<Base, T>::value;
	}

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

	float MousePicker::CheckCollision(const Collider* aabb)
	{
		float t1 = (aabb->GetMinExtends().x - m_Camera->GetPosition().x) / m_CurrentRay.x;
		float t2 = (aabb->GetMaxExtends().x - m_Camera->GetPosition().x) / m_CurrentRay.x;
		float t3 = (aabb->GetMinExtends().y - m_Camera->GetPosition().y) / m_CurrentRay.y;
		float t4 = (aabb->GetMaxExtends().y - m_Camera->GetPosition().y) / m_CurrentRay.y;
		float t5 = (aabb->GetMinExtends().z - m_Camera->GetPosition().z) / m_CurrentRay.z;
		float t6 = (aabb->GetMaxExtends().z - m_Camera->GetPosition().z) / m_CurrentRay.z;

		float tmin = glm::max(glm::max(glm::min(t1, t2), glm::min(t3, t4)), glm::min(t5, t6));
		float tmax = glm::min(glm::min(glm::max(t1, t2), glm::max(t3, t4)), glm::max(t5, t6));

		if (tmax < 0.0f) 
		{
			//std::cout << "Collider behind camera" << std::endl;

			return -1.0f;
		}

		if (tmin > tmax) 
		{
			//std::cout << "No collision" << std::endl;
			return -1.0f;
		}

		if (tmin < 0.0f) 
		{
			//std::cout << "Collision detected" << std::endl;
			return tmax;
		}
		//std::cout << "Collision detected" << std::endl;
		return tmin;
	}

	glm::vec3 MousePicker::GetPickedObject(glm::vec3 originalPosition)
	{
		float checkCollisionResult;
		for (int i = 0; i < PhysicsEngine::GetInstance()->GetNumObjects() ; i++)
		{
			checkCollisionResult = CheckCollision(&PhysicsEngine::GetInstance()->GetObject(i).GetCollider());
			if (checkCollisionResult != -1) {
				//vector of collider's position  
				glm::vec3 vectorGameObject = PhysicsEngine::GetInstance()->GetObject(i).GetPosition();
				for (int j = 0; j < RenderEngine::GetInstance()->map->GetAllChildren().size(); j++) {
					glm::vec3 position = RenderEngine::GetInstance()->map->GetAllChildren()[j]->GetTransform().GetPos();
					
					//for (auto it = RenderEngine::GetInstance()->treeTransforms.begin(); it != RenderEngine::GetInstance()->treeTransforms.end();) {
					//	if (vectorGameObject == it->GetPos()) {
					//		RenderEngine::GetInstance()->treeTransforms.erase(it);
					//	}
					//}
					for (int k = 0; k < RenderEngine::GetInstance()->treeTransforms.size(); k++) {
						if (vectorGameObject == RenderEngine::GetInstance()->treeTransforms[k].GetPos()) {
							RenderEngine::GetInstance()->wasCut = true;
							RenderEngine::GetInstance()->treeTransforms.erase(RenderEngine::GetInstance()->treeTransforms.begin() + k);
						}
					}

					//if (position == vectorGameObject && RenderEngine::GetInstance()->map->GetAllChildren()[j]->GetM_Tag() == "tree") {
					//	RenderEngine::GetInstance()->map->GetAllChildren()[j]->SetWasCut(true);
					//	std::cout << "tree: " << j << " " << RenderEngine::GetInstance()->map->GetAllChildren()[j]->GetWasCut()<<  std::endl;
					//}
				}
				return PhysicsEngine::GetInstance()->GetObject(i).GetPosition();
			}
		}
		return originalPosition;
	}

	void MousePicker::HandleEvent(Event* event)
	{
		if (event->GetEventId() == "move")
		{
			RenderModelComponent* rmc = (RenderModelComponent*)event->GetParameter();
			glm::vec3 vec3 = GetPickedObject(rmc->m_Transform.GetPos());
			rmc->m_Transform.SetPos(vec3);
		}
	}
}