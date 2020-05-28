#pragma once

#include "../PhysicsEngine/Aabb.h"
#include "../RenderEngine/Shader.h"

namespace Clumsy
{
	class Button
	{
	public:
		Button(glm::vec2 corner, float height, float width, std::string text, glm::vec3 color);
		~Button() { CleanUp(); }
		void Render(Shader* shader);
		void OnClick();
		void CleanUp();

		std::string GetText() { return m_Text; }
		Aabb* GetCollider() { return m_Collider; }

	private:
		glm::vec2 m_Corner;
		float m_Height;
		float m_Width;
		glm::vec3 m_Min;
		glm::vec3 m_Max;
		std::string m_Text;
		glm::vec3 m_Color;
		Aabb* m_Collider;
		unsigned int VBO, VAO;
	};
}
