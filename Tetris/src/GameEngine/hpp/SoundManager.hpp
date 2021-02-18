#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <unordered_map>

namespace hgw
{
	class SoundManager
	{
	public:
		SoundManager() {};
		~SoundManager() {};

		void Play(std::string keyName);

		void setGlobalVolume(float volume);
		float getGlobalVolume();

		void AddSound(std::string sound_keyName, std::string filename);
		void setAllSoundsToGlobalVolume();
	private:
		float globalVolume = 100.0f;

		void LoadSoundBuffer(std::string name, std::string filename);
		sf::SoundBuffer &GetSoundBuffer(std::string name);

		std::map<std::string, sf::SoundBuffer> _soundBuffers;
		std::unordered_map<std::string, sf::Sound> _sounds;
	};
}