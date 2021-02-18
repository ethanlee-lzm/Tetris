#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include <fstream>

namespace hgw
{
	class MenuState : public State
	{
	public:
		MenuState(GameDataRef _data);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	
	private:
		GameDataRef _data;

		sf::Sound clear1, clear2, clear3, clear4;
		sf::Music gameMusic, menuMusic;

		sf::Text tetrisText;
		sf::Text singlePlayerText;
		sf::Text multiPlayerText;
		sf::Text settingsText;
		sf::Text exitText;
	};
}