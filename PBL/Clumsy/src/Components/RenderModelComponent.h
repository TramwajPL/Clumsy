#pragma once

#include <glm/gtx/string_cast.hpp>

#include "../RenderEngine/Model.h"
#include "../Core/EntityComponent.h"

namespace Clumsy {

	class RenderModelComponent : public EntityComponent
	{
	public:
		RenderModelComponent(Model* model, Transform transform, float angle) : m_Model(model), m_Transform(transform), m_Angle(angle)
		{
			//delete constructor in EntityComponent.h
		}

		virtual void Render(Shader& shader) 

		{
			//shader.use();
			glm::mat4 model = glm::mat4(1.0f);

			model = glm::translate(model, m_Transform.GetPos());
			glm::vec3 vec;
			vec.x = m_Transform.GetRot()->x;
			vec.y = m_Transform.GetRot()->y;
			vec.z = m_Transform.GetRot()->z;
			model = glm::rotate(model, glm::radians(m_Angle), vec);
			model = glm::scale(model, glm::vec3(m_Transform.GetScale()));

			shader.setMat4("model", model);

			if (m_Model->hasBones) {
				m_Model->Draw(shader);
			}
			else
				m_Model->Draw2(shader);
			
		}

		void SetTransform(glm::vec3 tr)
		{
			m_Transform.SetPos(tr);
		}

		virtual void Update() 
		{
			//glm::vec3 pos = GetParentTransform().GetPos();
			//m_Transform.SetPos(pos);
			//SetTransform(GetParentTransform());
			SetTransform(m_Transform.GetPos());
		}

		Transform m_Transform;

	private:
		float m_Angle;
		Model* m_Model;
	};
}