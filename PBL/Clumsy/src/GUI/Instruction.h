#pragma once

#include "../RenderEngine/Shader.h"

namespace Clumsy
{
	class Instruction {
	public:
		Instruction(std::string pathToTexture, Shader* shader);
		void Render();
		void loadTexture(std::string path);

	private:
		unsigned int VAO, VBO, texture;
		Shader* shader;
	
	};
}