#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

namespace hgw
{
	class MusicManager
	{
	public:
		void Play(std::string keyName);
		void Pause(std::string keyName);
		void Stop(std::string keyName);

		void setGlobalVolume(float volume);
		float getGlobalVolume();

		void AddSong(std::string keyName, std::string filepath, bool loop);
		void setAllSongsToGlobalVolume();
	private:
		float globalVolume = 100.0f;

		std::unordered_map<std::string, sf::Music> _music;
	};
}