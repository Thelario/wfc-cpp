#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

namespace Satellite
{
	enum class KeyCode
	{
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, Ñ, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		ESCAPE, TAB, CTRL, ALT, INTRO, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIXE, SEVEN, EIGHT, NINE,
		SPACE
	};

	struct KeyEvent
	{
		bool key_down;
		bool key_up;

		KeyEvent(bool key_down, bool key_up)
			: key_down(key_down), key_up(key_up)
		{ }
	};

	class InputManager
	{
	private:
		static std::unordered_map<KeyCode, KeyEvent> keys;
		static glm::vec2 mouse_position;

		static bool left_mouse_button_down;
		static bool right_mouse_button_down;
		static bool left_mouse_button_up;
		static bool right_mouse_button_up;

	public:
		static void ResetKeyStates();

		static void SetKey(KeyCode key_code, bool value);
		static bool GetKeyDown(KeyCode key_code);
		static bool GetKeyUp(KeyCode key_code);

		static void SetMousePosition(glm::vec2 mouse_pos);
		static glm::vec2 GetMousePosition();

		static void SetMouseButtonDown(short int button, bool value);
		static void SetMouseButtonUp(short int button, bool value);
		static bool GetMouseButtonDown(short int button);
		static bool GetMouseButtonUp(short int button);
	};
}