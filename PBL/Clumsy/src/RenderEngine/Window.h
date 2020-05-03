#pragma once

#include <glad/glad.h>
#include <glfw3.h>

#include "../Core/Game.h"

namespace Clumsy {

	class Window {

	public:
		Window(int width, int height);

		virtual ~Window();
		void Init(int width, int height);
		void render(GLFWwindow* window);
		bool IsCloseRequested() const { return m_IsCloseRequested; };
		void SetIsCloseRequested(bool value) { m_IsCloseRequested = value; }
		GLFWwindow* GetGLFWWindow() { return m_GLFWWindow; }

		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }

	private:
		int m_Width;
		int m_Height;
		bool isRunning = false;
		bool m_IsCloseRequested;
		Game game;
		GLFWwindow* m_GLFWWindow;
	};
}