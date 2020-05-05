#pragma once
#include "../Core/EntityComponent.h"
#include "../Core/Input.h"
#include "glm/ext.hpp"

namespace Clumsy {
	class MoveComponent : public EntityComponent {
	public:
		void Move(glm::vec3 direction ) {
			GetParentTransform().SetPos(GetParentTransform().GetPos() + direction);
		}

		virtual void ProcessInput(int input) {
			if (input == 3) {
				GetParentTransform().SetPos(GetParentTransform().GetPos() + glm::vec3(0.0f, 0.1f, 0.0f)); //probably forward
				std::cout << "UP" << std::endl;
				std::cout << glm::to_string(GetParentTransform().GetPos()) << std::endl;

			}
			if (input == 4) {
				Move(glm::vec3(0.0f, 0.0f, 0.2f)); //probably backward
				std::cout << "DOWN" << std::endl;
			}
			if (input == 1) {
				Move(glm::vec3(0.0f, -0.2f, 0.0f)); //probably left
				std::cout << "LEFT" << std::endl;
			}
			if (input == 2) {
				Move(glm::vec3(0.0f, 0.2f, 0.0f)); //probably right
				std::cout << "RIGHT" << std::endl;
			}
		}
			
	private:

	};
}