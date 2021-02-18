#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include <SFML/Network.hpp>
#include <thread>
#include <future>

namespace hgw
{
	class ConnectState : public State
	{
	public:
		ConnectState(GameDataRef _data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		char getPressedDigit(sf::Event event, bool withDot);

	private:
		GameDataRef _data;

		sf::Text createGameText, joinGameText; //join or create choice
		bool isJoiningGame = false, isCreatingGame = false;

		sf::Text localIPText, localPortText; //create game
		std::thread connectionThread;
		sf::Text waitingForConnectionText;
		sf::Clock waitingClock;
		std::string waitingDots = "";
		bool dotsGoingForward = true;
		unsigned short localport = 0;
		sf::TcpSocket client;
		std::future<bool> gameCreated;

		sf::Text ipConnectText, portConnectText, serverIpText, serverPortText; //join game
		sf::IpAddress ipToConnectTo;
		unsigned short portToConnectTo;
		bool isTypingIp = true, isTypingPort = false;
		bool isIpFullyEnterd = false, isPortFullyEnterd = false;
		std::string ipDigitsEntered = "", portDigitsEntered = "";
		std::string textCursor = "|";
		sf::FloatRect ipFloatRect, portFloatRect;
		sf::TcpSocket socket;
		bool cursorChanged = false;
		sf::Text joinMatchText;
	};
}