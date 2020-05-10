#pragma once

#include "../Core/Input.h"
#include "../Core/EntityComponent.h"

namespace Clumsy 
{
	class MoveComponent : public EntityComponent 
	{
	public:

		MoveComponent() {}

		void Move(glm::vec3 direction ) {}

		virtual void ProcessInput(int input) 
		{
			if (input == 3) 
			{
				Move(glm::vec3(0.0f, 0.0f, 11.2f));
				std::cout << "UP" << std::endl;
				std::cout << glm::to_string(GetParentTransform().GetPos()) << std::endl;
			}
			else if (input == 4) 
			{
				Move(glm::vec3(0.0f, 0.0f, 10.2f)); //probably backward
				std::cout << "DOWN" << std::endl;
				std::cout << glm::to_string(GetParentTransform().GetPos()) << std::endl;
			}
			else if (input == 1) 
			{
				Move(glm::vec3(0.0f, -0.2f, 0.0f)); //probably left
				std::cout << "LEFT" << std::endl;
			}
			else if (input == 2) 
			{
				Move(glm::vec3(0.0f, 0.2f, 0.0f)); //probably right
				std::cout << "RIGHT" << std::endl;
			}
		}
			
	private:

	};
}