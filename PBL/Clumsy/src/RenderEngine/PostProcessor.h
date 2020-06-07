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
		GLboolean m_Reverse, m_Shake, m_Blur;

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