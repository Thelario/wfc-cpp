#pragma once

#include "../Engine/Game.h"
#include "../Engine/Button.h"

using namespace Satellite;

namespace Demo
{
	class WfcDemo : public Game
	{
		Button* solve_button;
		Button* reset_button;

		void Start() override;
		void Update() override;
		void Render() override;
	};
}