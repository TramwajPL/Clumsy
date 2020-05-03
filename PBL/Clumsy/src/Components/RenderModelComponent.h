#pragma once
#include "../Core/EntityComponent.h"
#include "../RenderEngine/Model.h"

namespace Clumsy {
	class RenderModelComponent : public EntityComponent {
	public:
		RenderModelComponent(Model model) : m_Model(model) {
			//delete constructor in EntityComponent.h
		}

		virtual void Render(Shader& shader) {
			shader.use();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.3f, -1.8f));
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
			shader.setMat4("model", model);
			m_Model.Draw(shader);
			//TODO: renderowanie modelu
		}
	private:
		Model m_Model;

	};
}