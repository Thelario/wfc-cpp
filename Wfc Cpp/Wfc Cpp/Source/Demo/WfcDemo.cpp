#include "WfcDemo.h"

#include "../Engine/FontsManager.h"
#include "../Engine/Engine.h"

#include "TilesManager.h"
#include "Grid.h"

namespace Demo
{
	void WfcDemo::Start()
	{
		Engine::Instance()->SetDebugging(true);
		Engine::Instance()->SetRenderLogicalSize(glm::vec2(480, 270));
		Engine::Instance()->SetWindowTitle("Wave Function Collapse Demo");
		Engine::Instance()->SetBackgroundColor({ 25, 25, 25, 255 });

		FontsManager::Instance()->AddFont("arial", "arial.ttf", 100);

		TilesManager::Instance()->Start();
		Grid::Instance()->CreateGrid();

		solve_button = new Button(glm::vec2(82.5, 165), glm::vec2(.75), 0, "empty-tile", 64, 32, false, 2, true, 0, SDL_Color({ 155, 155, 155, 255 }),
			true, true, false, glm::vec2(0), glm::vec2(0), ColliderTag::NONE, glm::vec2(82.5, 165), glm::vec2(.15), "Solve", true, "arial");

		reset_button = new Button(glm::vec2(82.5, 200), glm::vec2(.75), 0, "empty-tile", 64, 32, false, 3, true, 0, SDL_Color({ 155, 155, 155, 255 }),
			true, true, false, glm::vec2(0), glm::vec2(0), ColliderTag::NONE, glm::vec2(82.5, 200), glm::vec2(.15), "Reset", true, "arial");
	}

	void WfcDemo::Update()
	{
		Game::Update();
		Grid::Instance()->Update();
		solve_button->Update();
		reset_button->Update();
	}

	void WfcDemo::Render()
	{
		Game::Render();
		solve_button->Render();
		reset_button->Render();
	}
}
