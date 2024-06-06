#include "Engine.h"

#include <iostream>
#include <ctime>
#include <chrono>

#include "InputManager.h"
#include "LoggerManager.h"
#include "FontsManager.h"
#include "SoundsManager.h"
#include "TexturesManager.h"

namespace Satellite
{
    const char* title = "Satellite";

	Engine* Engine::Instance()
	{
        static Engine* instance = new Engine();
		return instance;
	}

	void Engine::Start(Game* game_to_run)
	{
		// Start up engine systems in the correct order.

        fps = 0;
        frame_count = 0;
        time_passed = 0;

        // Initialize variables that can later be changed
        real_window_size = glm::vec2(960, 540);
        render_logical_size = glm::vec2(960, 540);

		// Initializing SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			LoggerManager::Error("An error was produced when initializing SDL: ", SDL_GetError());
			is_running = false;
			return;
		}

        // Initialize TTF
        if (FontsManager::Instance()->Start() == false) {
            is_running = false;
            return;
        }

		// Creating SDL Window
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, real_window_size.x, real_window_size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == NULL) {
			LoggerManager::Error("An error was produced when creating SDL window: ", SDL_GetError());
			is_running = false;
			return;
		}

		// Creating SDL Renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			LoggerManager::Error("An error was produced when creating SDL renderer: ", SDL_GetError());
			is_running = false;
			return;
		}

        // Initialize SDL_Mixer
        if (SoundsManager::Instance()->Start() == false) {
            is_running = false;
            return;
        }

        // Initialize Texture Manager
		TexturesManager::Instance()->Start(renderer);

		// Creating random based on system time
		auto now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		std::tm local_tm;
		localtime_s(&local_tm, &now_time);
		int seed = (local_tm.tm_hour * 60 * 60) + (local_tm.tm_min * 60) + local_tm.tm_sec;
		random = new Random(seed);

        // Start the selected game
        game = game_to_run;
        game->Start();

        // After the game has had a chance to change some of the Engine values, apply those engine values
        if (SDL_RenderSetLogicalSize(renderer, render_logical_size.x, render_logical_size.y) != 0) {
            LoggerManager::Error("An error was produced when setting up the render logical size: ", SDL_GetError());
            is_running = false;
            return;
        }

		is_running = true;
	}

	void Engine::Run()
	{
		while (is_running)
		{
			ProcessInput();
            Update();
            game->HandleCollisions();
            Render();
            game->CreateGameObjects();
            game->DestroyGameObjects();
		}
	}

    void Engine::ProcessInput()
    {
        SDL_Event event;

        InputManager::ResetKeyStates();

        while (SDL_PollEvent(&event)) // Iterating through all the possible events that might have happened in this frame
        {
            Uint32 buttonState = SDL_GetMouseState(NULL, NULL);
            switch (event.type)
            {
            case SDL_QUIT:
                is_running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    InputManager::SetKey(KeyCode::A, true);
                    break;
                case SDLK_b:
                    InputManager::SetKey(KeyCode::B, true);
                    break;
                case SDLK_c:
                    InputManager::SetKey(KeyCode::C, true);
                    break;
                case SDLK_d:
                    InputManager::SetKey(KeyCode::D, true);
                    break;
                case SDLK_e:
                    InputManager::SetKey(KeyCode::E, true);
                    break;
                case SDLK_f:
                    InputManager::SetKey(KeyCode::F, true);
                    break;
                case SDLK_g:
                    InputManager::SetKey(KeyCode::G, true);
                    break;
                case SDLK_h:
                    InputManager::SetKey(KeyCode::H, true);
                    break;
                case SDLK_i:
                    InputManager::SetKey(KeyCode::I, true);
                    break;
                case SDLK_j:
                    InputManager::SetKey(KeyCode::J, true);
                    break;
                case SDLK_k:
                    InputManager::SetKey(KeyCode::K, true);
                    break;
                case SDLK_l:
                    InputManager::SetKey(KeyCode::L, true);
                    break;
                case SDLK_m:
                    InputManager::SetKey(KeyCode::M, true);
                    break;
                case SDLK_n:
                    InputManager::SetKey(KeyCode::N, true);
                    break;
                case SDLK_o:
                    InputManager::SetKey(KeyCode::O, true);
                    break;
                case SDLK_p:
                    InputManager::SetKey(KeyCode::P, true);
                    break;
                case SDLK_q:
                    InputManager::SetKey(KeyCode::Q, true);
                    break;
                case SDLK_r:
                    InputManager::SetKey(KeyCode::R, true);
                    break;
                case SDLK_s:
                    InputManager::SetKey(KeyCode::S, true);
                    break;
                case SDLK_t:
                    InputManager::SetKey(KeyCode::T, true);
                    break;
                case SDLK_u:
                    InputManager::SetKey(KeyCode::U, true);
                    break;
                case SDLK_v:
                    InputManager::SetKey(KeyCode::V, true);
                    break;
                case SDLK_w:
                    InputManager::SetKey(KeyCode::W, true);
                    break;
                case SDLK_x:
                    InputManager::SetKey(KeyCode::X, true);
                    break;
                case SDLK_y:
                    InputManager::SetKey(KeyCode::Y, true);
                    break;
                case SDLK_z:
                    InputManager::SetKey(KeyCode::Z, true);
                    break;
                case SDLK_ESCAPE:
                    InputManager::SetKey(KeyCode::ESCAPE, true);
                    break;
                case SDLK_TAB:
                    InputManager::SetKey(KeyCode::TAB, true);
                    break;
                case SDLK_SPACE:
                    InputManager::SetKey(KeyCode::SPACE, true);
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    InputManager::SetKey(KeyCode::A, false);
                    break;
                case SDLK_b:
                    InputManager::SetKey(KeyCode::B, false);
                    break;
                case SDLK_c:
                    InputManager::SetKey(KeyCode::C, false);
                    break;
                case SDLK_d:
                    InputManager::SetKey(KeyCode::D, false);
                    break;
                case SDLK_e:
                    InputManager::SetKey(KeyCode::E, false);
                    break;
                case SDLK_f:
                    InputManager::SetKey(KeyCode::F, false);
                    break;
                case SDLK_g:
                    InputManager::SetKey(KeyCode::G, false);
                    break;
                case SDLK_h:
                    InputManager::SetKey(KeyCode::H, false);
                    break;
                case SDLK_i:
                    InputManager::SetKey(KeyCode::I, false);
                    break;
                case SDLK_j:
                    InputManager::SetKey(KeyCode::J, false);
                    break;
                case SDLK_k:
                    InputManager::SetKey(KeyCode::K, false);
                    break;
                case SDLK_l:
                    InputManager::SetKey(KeyCode::L, false);
                    break;
                case SDLK_m:
                    InputManager::SetKey(KeyCode::M, false);
                    break;
                case SDLK_n:
                    InputManager::SetKey(KeyCode::N, false);
                    break;
                case SDLK_o:
                    InputManager::SetKey(KeyCode::O, false);
                    break;
                case SDLK_p:
                    InputManager::SetKey(KeyCode::P, false);
                    break;
                case SDLK_q:
                    InputManager::SetKey(KeyCode::Q, false);
                    break;
                case SDLK_r:
                    InputManager::SetKey(KeyCode::R, false);
                    break;
                case SDLK_s:
                    InputManager::SetKey(KeyCode::S, false);
                    break;
                case SDLK_t:
                    InputManager::SetKey(KeyCode::T, false);
                    break;
                case SDLK_u:
                    InputManager::SetKey(KeyCode::U, false);
                    break;
                case SDLK_v:
                    InputManager::SetKey(KeyCode::V, false);
                    break;
                case SDLK_w:
                    InputManager::SetKey(KeyCode::W, false);
                    break;
                case SDLK_x:
                    InputManager::SetKey(KeyCode::X, false);
                    break;
                case SDLK_y:
                    InputManager::SetKey(KeyCode::Y, false);
                    break;
                case SDLK_z:
                    InputManager::SetKey(KeyCode::Z, false);
                    break;
                case SDLK_ESCAPE:
                    InputManager::SetKey(KeyCode::ESCAPE, false);
                    break;
                case SDLK_TAB:
                    InputManager::SetKey(KeyCode::TAB, false);
                    break;
                case SDLK_SPACE:
                    InputManager::SetKey(KeyCode::SPACE, false);
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                InputManager::SetMousePosition(glm::vec2(event.motion.x, event.motion.y));
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    InputManager::SetMouseButtonDown(0, true);
                    break;
                case SDL_BUTTON_RIGHT:
                    InputManager::SetMouseButtonDown(1, true);
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    InputManager::SetMouseButtonDown(0, false);
                    InputManager::SetMouseButtonUp(0, true);
                    break;
                case SDL_BUTTON_RIGHT:
                    InputManager::SetMouseButtonDown(1, false);
                    InputManager::SetMouseButtonUp(1, true);
                    break;
                }
                break;
            }
        }
    }

    void Engine::Update()
    {
        // Capping frame rate

        int time_to_wait = MILLISECS_PER_FRAME - (SDL_GetTicks() - milliseconds_previous_frame);
        if (time_to_wait > 0 && time_to_wait <= MILLISECS_PER_FRAME) {
            SDL_Delay(time_to_wait);
        }

        // Calculating delta time

        delta_time = (SDL_GetTicks() - milliseconds_previous_frame) / 1000.0;
        if (delta_time > 1000) {
            delta_time = 0;
        }
        
        time_passed += delta_time;

        milliseconds_previous_frame = SDL_GetTicks();

        // Updating all the game

        game->Update();

        // Calculating real fps

        frame_count++;
        if (time_passed >= 1)
        {
            time_passed = 0;
            fps = frame_count;
            frame_count = 0;
        }     
    }

    void Engine::Render()
    {
        SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a);
        SDL_RenderClear(renderer);

        game->Render();

        SDL_RenderPresent(renderer);
    }

	void Engine::Destroy()
	{
		// Shut everything down, in reverse order.

		game->Destroy();
        
        delete random;

        TexturesManager::Instance()->Destroy();
        SoundsManager::Instance()->Destroy();
        FontsManager::Instance()->Destroy();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_Quit();
        TTF_Quit();
        SDL_Quit();
	}

    // Creating and destroying gameobjects

    GameObject* Engine::CreateObject(GameObject* gameobject) { return game->CreateObject(gameobject); }
    void Engine::DestroyObject(GameObject* gameobject) { game->DestroyObject(gameobject); }
    void Engine::DestroyObjects() { game->DestroyObjects(); }
    void Engine::DestroyObjects(std::vector<GameObject*> gameobjects)
    {
        for (GameObject* gameobject : gameobjects) {
            DestroyObject(gameobject);
        }
    }

    // Getters to some of the engine variables

    bool Engine::Debugging() { return debug; }
    int Engine::GetWindowWidth() { return render_logical_size.x; }
    int Engine::GetWindowHeight() { return render_logical_size.y; }
    double Engine::GetDeltaTime() { return delta_time; }
    SDL_Renderer* Engine::GetRenderer() { return renderer; }
    Random* Engine::GetRandom() { return random; }

    // Setters to some of the engine variables

    void Engine::SetDebugging(bool debug) { this->debug = debug; }
    void Engine::SetFullsCreen(bool fullscreen) { SDL_SetWindowFullscreen(window, fullscreen ? 0 : SDL_WINDOW_FULLSCREEN); }
    void Engine::SetBackgroundColor(SDL_Color color) { background_color = color; }
    void Engine::SetIsRunning(bool is_running) { this->is_running = is_running; }
    void Engine::SetWindowTitle(const char* new_title) { SDL_SetWindowTitle(window, new_title); }
    void Engine::SetRealWindowSize(glm::vec2 window_size) { real_window_size = window_size; }
    void Engine::SetRenderLogicalSize(glm::vec2 logical_size) { render_logical_size = logical_size; }
}