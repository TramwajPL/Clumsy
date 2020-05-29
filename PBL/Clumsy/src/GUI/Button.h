#pragma once

#include "../PhysicsEngine/Aabb.h"
#include "../RenderEngine/Shader.h"

namespace Clumsy
{
	class Button
	{
	public:
		Button(glm::vec2 corner, std::string text, glm::vec3 color);
		~Button() { CleanUp(); }
		void Render(Shader* shader);
		void OnClick();
		void CleanUp();

		std::string GetText() { return m_Text; }
		glm::vec2 GetCorner() { return m_Corner; }

	private:
		glm::vec2 m_Corner;
		std::string m_Text;
		glm::vec3 m_Color;
		unsigned int VBO, VAO;
	};
}
