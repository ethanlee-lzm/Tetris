#include "src/GameEngine/hpp/DataManager.hpp"

#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/serialization/binary_object.hpp"
#include "boost/serialization/serialization.hpp"
#include "boost/serialization/binary_object.hpp"

#include <iostream>
#include <filesystem>

namespace hgw
{
	namespace ar = boost::archive;
	using boost::serialization::make_binary_object;

	SaveGameData::SaveGameData(int highScore, bool fullGrid, bool originalColors, float soundVolume, float musicVolume)
	{
		
		this->highScore = highScore;

		this->fullGrid = fullGrid;
		this->originalColors = originalColors;

		this->soundVolume = soundVolume;
		this->musicVolume = musicVolume;
	}


	void DataManager::serializeSave()
	{
		gameDataFile.open("data.dat", std::fstream::out);

		if (gameDataFile.good())
		{
			ar::binary_oarchive oarchive{ gameDataFile, ar::no_header };
			oarchive << gameData;
		}
		else if(!std::filesystem::exists("data.dat"))
		{
			std::cout << "File doesn't exists" << std::endl;
		}
		else
		{
			std::cout << "Unable to open file { Serialization Save }" << std::endl;
		}

		gameDataFile.close();
	}

	void DataManager::serializeLoad()
	{
		gameDataFile.open("data.dat", std::fstream::in);

		if (gameDataFile.good())
		{
			ar::binary_iarchive iarchive{ gameDataFile, ar::no_header};
			iarchive >> gameData;
		}
		else if (!std::filesystem::exists("data.dat"))
		{
			std::cout << "File doesn't exists" << std::endl;
		}
		else
		{
			std::cout << "Unable to open file { Serialization Load }" << std::endl;
		}

		gameDataFile.close();
	}
}