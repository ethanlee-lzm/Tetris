#include "src/GameEngine/hpp/MusicManager.hpp"
#include <iostream>

namespace hgw
{
	void MusicManager::Play(std::string keyName)
	{
		_music[keyName].setVolume(globalVolume);
		_music[keyName].play();
	}

	void MusicManager::Pause(std::string keyName)
	{
		_music[keyName].pause();
	}

	void MusicManager::Stop(std::string keyName)
	{
		_music[keyName].stop();
	}

	void MusicManager::AddSong(std::string keyName, std::string filepath, bool loop = true)
	{
		_music[keyName].setVolume(globalVolume);
		_music[keyName].openFromFile(filepath);
		_music[keyName].setLoop(loop);
	}

	void MusicManager::setGlobalVolume(float volume)
	{
		globalVolume = volume;
	}

	float MusicManager::getGlobalVolume()
	{
		return globalVolume;
	}

	void MusicManager::setAllSongsToGlobalVolume()
	{
		for (auto &m : _music)
		{
			m.second.setVolume(globalVolume);
		}
	}
}