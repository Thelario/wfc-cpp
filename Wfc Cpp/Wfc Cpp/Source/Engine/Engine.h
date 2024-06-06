#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

#include "Game.h"
#include "Random.h"

namespace Satellite
{
	const int FPS = 60;
	const int MILLISECS_PER_FRAME = 1000 / FPS;

	class Engine
	{
		private:
			bool is_running;
			bool debug;
			
			int fps;
			int frame_count;
			Uint32 milliseconds_previous_frame;
			double time_passed;
			double delta_time;

			SDL_Color background_color;
			glm::vec2 real_window_size;
			glm::vec2 render_logical_size;

			SDL_Window* window;
			SDL_Renderer* renderer;
			Random* random;
			Game* game;

		public:
			static Engine* Instance();

			void Start(Game* game_to_run);
			void Run();
			void Destroy();

			void ProcessInput();
			void Update();
			void Render();

			GameObject* CreateObject(GameObject* gameobject);
			void DestroyObject(GameObject* gameobject);
			void DestroyObjects();
			void DestroyObjects(std::vector<GameObject*> gameobjects);

			bool Debugging();
			int GetWindowWidth();
			int GetWindowHeight();
			double GetDeltaTime();
			SDL_Renderer* GetRenderer();
			Random* GetRandom();

			void SetDebugging(bool debug);
			void SetFullsCreen(bool fullscreen);
			void SetBackgroundColor(SDL_Color color);
			void SetIsRunning(bool is_running);
			void SetWindowTitle(const char* new_title);
			void SetRealWindowSize(glm::vec2 window_size);
			void SetRenderLogicalSize(glm::vec2 logical_size);
	};
}