#include "WfcDemo.h"

#include "../Engine/FontsManager.h"
#include "../Engine/Engine.h"

#include "TilesManager.h"
#include "Grid.h"

namespace Demo
{
	void Demo::WfcDemo::Start()
	{
		Engine::Instance()->SetDebugging(true);
		Engine::Instance()->SetRenderLogicalSize(glm::vec2(480, 270));
		Engine::Instance()->SetWindowTitle("Wave Function Collapse Demo");
		Engine::Instance()->SetBackgroundColor({ 25, 25, 25, 255 });

		FontsManager::Instance()->AddFont("arial", "arial.ttf", 100);

		TilesManager::Instance()->Start();
		Grid::Instance()->CreateGrid();
	}

	void Demo::WfcDemo::Update()
	{
		Game::Update();
	}

	void Demo::WfcDemo::Render()
	{
		Game::Render();
	}
}
