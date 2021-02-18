#include <iostream>
#include "src/GameEngine/hpp/Game.hpp"
#include "DEFINE.hpp"

int main()
{
	hgw::Game(APP_WIDTH, APP_HEIGHT, APP_NAME); //crashes for state creation, we dont have states, crate state in game.cpp
	return 0;
}