#pragma once

#include <glad\glad.h>

#include "Shader.h"
#include "TextureClass.h"

namespace Clumsy
{
	class PostProcessor
	{
	public:
		Shader m_PostProcessingShader;
		TextureClass m_Texture;
		GLuint m_Width, m_Height;
		GLboolean m_Confuse, m_Chaos, m_Shake;

		PostProcessor(Shader shader, GLuint width, GLuint height);
		~PostProcessor() {}
		void BeginRender();
		void EndRender();
		void Render(GLfloat time);

	private:
		GLuint MSFBO, FBO;
		GLuint RBO; 
		GLuint VAO;

		void initRenderData();
	};
}