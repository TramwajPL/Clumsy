#pragma once
#include "../Core/EntityComponent.h"
#include "../RenderEngine/Model.h"

namespace Clumsy {
	class RenderModelComponent : public EntityComponent {
	public:
		RenderModelComponent(Model model) : m_Model(model){
			//delete constructor in EntityComponent.h
		}

		virtual void Render(Shader& shader) {
			shader.use();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, GetParentTransform().GetPos());
			model = glm::scale(model, glm::vec3(GetParentTransform().GetScale()));
			shader.setMat4("model", model);
			m_Model.Draw(shader);
			//TODO: renderowanie modelu
			//std::cout << "renderowanko" << std::endl;

		}
	private:
		Model m_Model;

	};
}