#include "WfcDemo.h"

#include "../Engine/Engine.h"

namespace Demo
{
	void Demo::WfcDemo::Start()
	{
		Engine::Instance()->SetDebugging(false);
		Engine::Instance()->SetRenderLogicalSize(glm::vec2(1920, 1080));
		Engine::Instance()->SetWindowTitle("Wave Function Collapse Demo");
		Engine::Instance()->SetBackgroundColor({ 25, 25, 25, 255 });
	}

	void Demo::WfcDemo::Update()
	{
	}

	void Demo::WfcDemo::Render()
	{
	}
}
