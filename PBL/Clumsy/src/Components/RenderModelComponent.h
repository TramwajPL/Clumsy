#pragma once
#include "../Core/EntityComponent.h"
#include "../RenderEngine/Model.h"
#include "glm/gtx/string_cast.hpp"

namespace Clumsy {
	class RenderModelComponent : public EntityComponent {
	public:
		RenderModelComponent(Model model, Transform transform) : m_Model(model), m_Transform(transform){
			//delete constructor in EntityComponent.h
		}

		virtual void Render(Shader& shader) {
			shader.use();
			glm::mat4 model = glm::mat4(1.0f);

			model = glm::translate(model, GetParentTransform().GetPos());
			//std::cout << "kupsko" << glm::to_string(m_Transform.GetPos()) << std::endl;
			glm::vec3 vec;
			vec.x = m_Transform.GetRot()->x;
			vec.y = m_Transform.GetRot()->y;
			vec.z = m_Transform.GetRot()->z;
			model = glm::rotate(model,glm::radians(90.0f), vec);
			model = glm::scale(model, glm::vec3(m_Transform.GetScale()));

			shader.setMat4("model", model);
			m_Model.Draw(shader);
		}

		virtual void Update() {
			glm::vec3 pos = GetParentTransform().GetPos();
			std::cout << "kupsko" << glm::to_string(pos) << std::endl;
			m_Transform.SetPos(pos);
		}

	private:
		Model m_Model;
		Transform m_Transform;

	};
}