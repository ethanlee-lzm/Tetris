#include "src/GameEngine/hpp/SoundManager.hpp"
#include <iostream>

namespace hgw
{
	void SoundManager::LoadSoundBuffer(std::string name, std::string filename)
	{
		sf::SoundBuffer sb;

		if (sb.loadFromFile(filename) && _soundBuffers.find(name) == _soundBuffers.end()) //if loaded properly and value doesn't exist in map
		{
			_soundBuffers[name] = sb;
		}
	}
	sf::SoundBuffer &SoundManager::GetSoundBuffer(std::string name)
	{
		return _soundBuffers.at(name);
	}

	void SoundManager::Play(std::string keyName)
	{
		_sounds[keyName].setVolume(globalVolume);
		_sounds[keyName].play();
	}

	void SoundManager::AddSound(std::string keyName, std::string filepath)
	{
		LoadSoundBuffer(keyName, filepath);
		_sounds[keyName].setBuffer(GetSoundBuffer(keyName));
		_sounds[keyName].setVolume(globalVolume);
	}

	void SoundManager::setGlobalVolume(float volume)
	{
		globalVolume = volume;
	}

	float SoundManager::getGlobalVolume()
	{
		return globalVolume;
	}

	void SoundManager::setAllSoundsToGlobalVolume()
	{
		for (auto &s : _sounds)
		{
			s.second.setVolume(globalVolume);
		}
	}
}