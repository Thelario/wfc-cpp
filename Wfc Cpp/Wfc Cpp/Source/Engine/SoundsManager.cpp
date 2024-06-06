#include "SoundsManager.h"

#include "LoggerManager.h"

namespace Satellite
{
	const std::string file_path = "./Assets/Sounds/";

	SoundsManager* SoundsManager::Instance()
	{
		static SoundsManager* instance = new SoundsManager();
		return instance;
	}

	bool SoundsManager::Start()
	{
		// Initializing SDL_Mixer

		Mix_Init(MIX_INIT_WAVPACK);

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
			LoggerManager::Error("SDL_mixer could not initialize! SDL_mixer Error: ", Mix_GetError());
			return false;
		}

		return true;
	}

	void SoundsManager::Destroy()
	{
		for (auto sound : _sounds) {
			Mix_FreeChunk(sound.second);
		}

		_sounds.clear();

		Mix_FreeMusic(_music);
	}

	void SoundsManager::AddSound(const std::string& file_name, const std::string& sound_id)
	{
		std::string new_string = file_path + file_name;

		Mix_Chunk* sound = Mix_LoadWAV(new_string.c_str());
		if (sound == NULL) {
			LoggerManager::Error("Failed to load sound! SDL_mixer Error: ", Mix_GetError());
		}

		_sounds.emplace(sound_id, sound);
	}

	void SoundsManager::PlayMusic()
	{
		if (_music == NULL) {
			LoggerManager::Error("Trying to play the music when it is NULL.");
			return;
		}

		Mix_PlayMusic(_music, -1);
	}

	void SoundsManager::PlaySound(const std::string& sound_id)
	{
		if (_sounds.find(sound_id) == _sounds.end()) {
			LoggerManager::Error("Trying to play a sound that does not exist.");
			return;
		}

		Mix_PlayChannel(-1, _sounds.at(sound_id), 0);
	}
}