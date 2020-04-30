#pragma once

namespace Clumsy {

	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImp(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImp(button); }
		inline static bool GetMouseX() { return s_Instance->GetMouseXImp(); }
		inline static bool GetMouseY() { return s_Instance->GetMouseYImp(); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImp(); }
	protected:
		virtual bool IsKeyPressedImp(int keycode) = 0;

		virtual bool IsMouseButtonPressedImp(int button) = 0;
		virtual float GetMouseXImp() = 0;
		virtual float GetMouseYImp() = 0;
		virtual std::pair<float, float> GetMousePositionImp() = 0;
	private:
		static Input* s_Instance;

	};
}