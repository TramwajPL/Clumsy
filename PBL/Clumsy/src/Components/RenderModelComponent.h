#pragma once
#include "../Core/EntityComponent.h"
#include "../RenderEngine/Model.h"

namespace Clumsy {
	class RenderModelComponent : public EntityComponent {
	public:
		RenderModelComponent(Model model, Transform transform) : m_Model(model), m_Transform(transform){
			//delete constructor in EntityComponent.h
		}

		virtual void Render(Shader& shader) {
			shader.use();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, m_Transform.GetPos());
			model = glm::scale(model, glm::vec3(m_Transform.GetScale()));
			shader.setMat4("model", model);
			m_Model.Draw(shader);
			//TODO: renderowanie modelu
			//std::cout << "renderowanko" << std::endl;

		}
	private:
		Model m_Model;
		Transform m_Transform;

	};
}