#pragma once

#include "../Engine/Game.h"

using namespace Satellite;

namespace Demo
{
	class WfcDemo : public Game
	{
		void Start() override;
		void Update() override;
		void Render() override;
	};
}