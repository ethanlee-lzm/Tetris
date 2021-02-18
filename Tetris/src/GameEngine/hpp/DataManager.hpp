#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

namespace hgw
{
	struct SaveGameData
	{
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar &highScore;

			ar &fullGrid;
			ar &originalColors;

			ar &soundVolume;
			ar &musicVolume;
		}

		SaveGameData() = default;
		SaveGameData(int highscore, bool fullGrid, bool originalColors, float soundVolume, float musicVolume);
		int highScore;

		bool fullGrid;
		bool originalColors;

		float soundVolume, musicVolume;
	};

	class DataManager
	{
	public:
		DataManager() {}
		~DataManager() {}

		void serializeSave();
		void serializeLoad();

		SaveGameData gameData;
		std::fstream gameDataFile;
	};
}