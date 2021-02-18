#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/GameEngine/hpp/Components.hpp"

namespace hgw
{
	class SettingsState : public State
	{
	public:
		SettingsState(GameDataRef _data, bool additionalBackOption = false);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		bool additionalBackOption;
		sf::Text returnText, additionalReturnText;
		sf::Text originalColorText, drawFullGridText;

		sf::Sprite soundOff, soundOn;
		sf::Sprite musicOff, musicOn;
		cmp::VolumeBar soundBar, musicBar;
		bool musicPointPressed = false, soundPointPressed = false;
		
		GameDataRef _data;
	};
}