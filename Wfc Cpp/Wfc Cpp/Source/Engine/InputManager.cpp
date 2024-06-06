#include "InputManager.h"

#include "LoggerManager.h"

namespace Satellite
{
	std::unordered_map<KeyCode, KeyEvent> InputManager::keys =
	{
		{ KeyCode::A, KeyEvent(false, false) },
		{ KeyCode::B, KeyEvent(false, false) },
		{ KeyCode::C, KeyEvent(false, false) },
		{ KeyCode::D, KeyEvent(false, false) },
		{ KeyCode::E, KeyEvent(false, false) },
		{ KeyCode::F, KeyEvent(false, false) },
		{ KeyCode::G, KeyEvent(false, false) },
		{ KeyCode::H, KeyEvent(false, false) },
		{ KeyCode::I, KeyEvent(false, false) },
		{ KeyCode::J, KeyEvent(false, false) },
		{ KeyCode::K, KeyEvent(false, false) },
		{ KeyCode::L, KeyEvent(false, false) },
		{ KeyCode::M, KeyEvent(false, false) },
		{ KeyCode::N, KeyEvent(false, false) },
		{ KeyCode::Ñ, KeyEvent(false, false) },
		{ KeyCode::O, KeyEvent(false, false) },
		{ KeyCode::P, KeyEvent(false, false) },
		{ KeyCode::Q, KeyEvent(false, false) },
		{ KeyCode::R, KeyEvent(false, false) },
		{ KeyCode::S, KeyEvent(false, false) },
		{ KeyCode::T, KeyEvent(false, false) },
		{ KeyCode::U, KeyEvent(false, false) },
		{ KeyCode::V, KeyEvent(false, false) },
		{ KeyCode::W, KeyEvent(false, false) },
		{ KeyCode::X, KeyEvent(false, false) },
		{ KeyCode::Y, KeyEvent(false, false) },
		{ KeyCode::Z, KeyEvent(false, false) },
		{ KeyCode::ESCAPE, KeyEvent(false, false) },
		{ KeyCode::TAB, KeyEvent(false, false) },
		{ KeyCode::SPACE, KeyEvent(false, false) }
	};

	glm::vec2 InputManager::mouse_position = glm::vec2(0);

	bool InputManager::left_mouse_button_down = false;
	bool InputManager::right_mouse_button_down = false;
	bool InputManager::left_mouse_button_up = false;
	bool InputManager::right_mouse_button_up = false;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setting the keys' states
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void InputManager::ResetKeyStates()
	{
		SetMouseButtonUp(0, false);
		SetMouseButtonUp(1, false);

		for (auto i = keys.begin(); i != keys.end(); i++) {
			i->second.key_up = false;
		}
	}

	void InputManager::SetKey(KeyCode key_code, bool value)
	{
		auto key = keys.find(key_code);

		if (key == keys.end()) {
			LoggerManager::Error("The key couldn't be found!!!");
			return;
		}

		key->second.key_down = value;

		if (value == false) {
			key->second.key_up = true;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getting the keys' states
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool InputManager::GetKeyDown(KeyCode key_code)
	{
		auto key = keys.find(key_code);

		if (key == keys.end()) {
			LoggerManager::Error("The key couldn't be found!!!");
			return false;
		}

		return key->second.key_down;
	}

	bool InputManager::GetKeyUp(KeyCode key_code)
	{
		auto key = keys.find(key_code);

		if (key == keys.end()) {
			LoggerManager::Error("The key couldn't be found!!!");
			return false;
		}

		return key->second.key_up;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setting and getting mouse position
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void InputManager::SetMousePosition(glm::vec2 mouse_pos)
	{
		mouse_position = mouse_pos;
	}

	glm::vec2 InputManager::GetMousePosition()
	{
		return mouse_position;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setting and getting mouse buttons left and right
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 0 for left button, 1 for right button
	void InputManager::SetMouseButtonDown(short int button, bool value)
	{
		switch (button)
		{
		case 0:
			left_mouse_button_down = value;
			break;
		case 1:
			right_mouse_button_down = value;
			break;
		}
	}

	// 0 for left button, 1 for right button
	void InputManager::SetMouseButtonUp(short int button, bool value)
	{
		switch (button)
		{
		case 0:
			left_mouse_button_up = value;
			break;
		case 1:
			right_mouse_button_up = value;
			break;
		}
	}

	// 0 for left button, 1 for right button
	bool InputManager::GetMouseButtonDown(short int button)
	{
		switch (button)
		{
		case 0:
			return left_mouse_button_down;
		case 1:
			return right_mouse_button_down;
		default:
			return false;
		}
	}

	// 0 for left button, 1 for right button
	bool InputManager::GetMouseButtonUp(short int button)
	{
		switch (button)
		{
		case 0:
			return left_mouse_button_up;
		case 1:
			return right_mouse_button_up;
		default:
			return false;
		}
	}
}