#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

namespace Clumsy {

	class RenderEngine;

	class Cube {
	public:

		Cube(glm::vec3 cubeTranslate, glm::vec3 cubeScale);
		void Render(Shader* shaderCube, unsigned int cubemapTexture);

	private:

		glm::vec3 m_CubeTranslate;
		glm::vec3 m_CubeScale;
		unsigned int cubeVAO, cubeVBO;

	};
}