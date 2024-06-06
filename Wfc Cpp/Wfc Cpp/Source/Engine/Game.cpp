#include "Game.h"

#include <iostream>

#include "LoggerManager.h"
#include "Utils.h"
#include "Engine.h"

namespace Satellite
{
	void Game::Start() {
		LoggerManager::Error("Careful, you are not overriding the base Game class (Start).");
	}

	void Game::Update()
	{
		// We only update objects that are enabled

		for (GameObject* gameobject : gameobjects)
		{
			if (gameobject != nullptr && gameobject->enabled == true) {
				gameobject->Update();
			}
		}
	}

	void Game::HandleCollisions()
	{
		// AABB Collision: expensive O(n^2) but easy to implement. Works for now...

		for (auto i = gameobjects.begin(); i != gameobjects.end(); i++)
		{
			auto a = *i;

			if (a->collidable == false) {
				continue;
			}

			for (auto j = (i + 1); j != gameobjects.end(); j++)
			{
				auto b = *j;

				if (b->collidable == false) {
					continue;
				}

				// First gameobject

				float a_pos_x = a->GetPosition().x - (a->GetSize().x / 2);
				float a_pos_y = a->GetPosition().y - (a->GetSize().y / 2);

				SDL_Rect a_rect = {
					static_cast<int>(a_pos_x + a->GetOffset().x),
					static_cast<int>(a_pos_y + a->GetOffset().y),
					static_cast<int>(a->GetSize().x),
					static_cast<int>(a->GetSize().y)
				};

				// Second gameobject

				float b_pos_x = b->GetPosition().x - (b->GetSize().x / 2);
				float b_pos_y = b->GetPosition().y - (b->GetSize().y / 2);

				SDL_Rect b_rect = {
					static_cast<int>(b_pos_x + b->GetOffset().x),
					static_cast<int>(b_pos_y + b->GetOffset().y),
					static_cast<int>(b->GetSize().x),
					static_cast<int>(b->GetSize().y)
				};

				// Collision check

				if (SDL_HasIntersection(&a_rect, &b_rect))
				{
					a->HandleCollisionEvent(b);
					b->HandleCollisionEvent(a);

					// Debugging collision info

					if (Engine::Instance()->Debugging() == false) {
						continue;
					}

					// const std::string a_name = Utils::GetTagName(a->GetTag());
					// const std::string b_name = Utils::GetTagName(b->GetTag());

					// LoggerManager::Log("Gameobject " + a_name + ": " + std::to_string(a_pos_x) + "," + std::to_string(a_pos_y));
					// LoggerManager::Log("Gameobject " + b_name + ": " + std::to_string(b_pos_x) + "," + std::to_string(b_pos_y));
					// LoggerManager::Log("Colliding: true");
					// LoggerManager::Log("");

					a->SetColliderColor({ 255, 0, 0, 255 });
					b->SetColliderColor({ 255, 0, 0, 255 });
				}
				else
				{
					a->RestartCollisionData(b);
					b->RestartCollisionData(a);

					if (Engine::Instance()->Debugging() == false) {
						continue;
					}

					// Debugging collision info

					// const std::string a_name = Utils::GetTagName(a->GetTag());
					// const std::string b_name = Utils::GetTagName(b->GetTag());

					// LoggerManager::Log("Gameobject " + a_name + ": " + std::to_string(a_pos_x) + "," + std::to_string(a_pos_y));
					// LoggerManager::Log("Gameobject " + b_name + ": " + std::to_string(b_pos_x) + "," + std::to_string(b_pos_y));
					// LoggerManager::Log("Colliding: false");
					// LoggerManager::Log("");

					a->SetColliderColor({ 0, 255, 0, 255 });
					b->SetColliderColor({ 0, 255, 0, 255 });
				}
			}
		}
	}

	void Game::Render()
	{
		// We only render objects that are enabled and are marked as renderable

		for (GameObject* gameobject : gameobjects)
		{
			if (gameobject != nullptr && gameobject->enabled == true && gameobject->renderable == true) {
				gameobject->Render();
			}
		}
	}

	void Game::Destroy()
	{
		for (GameObject* gameobject : gameobjects) {
			delete gameobject;
		}
	}

	GameObject* Game::CreateObject(GameObject* gameobject)
	{
		gameobjects_to_add.push_back(gameobject);
		return gameobject;
	}

	void Game::DestroyObject(GameObject* gameobject)
	{
		gameobjects_to_remove.push_back(gameobject);
	}

	void Game::DestroyObjects()
	{
		for (GameObject* gameobject : gameobjects) {
			DestroyObject(gameobject);
		}
	}

	void Game::CreateGameObjects()
	{
		for (GameObject* game_object : gameobjects_to_add) {
			game_object->Start();
			gameobjects.push_back(game_object);
		}

		gameobjects_to_add.clear();
	}

	void Game::DestroyGameObjects()
	{
		for (GameObject* element_to_remove : gameobjects_to_remove)
		{
			auto it = std::find(gameobjects.begin(), gameobjects.end(), element_to_remove);

			// Prevent deleting an object that was removed in a previous iteration of the loop
			if (it == gameobjects.end()) {
				continue;
			}

			gameobjects.erase(it);
			delete element_to_remove;
		}

		gameobjects_to_remove.clear();
	}

	int Game::GetGameObjectsCount() { return gameobjects.size(); }
}