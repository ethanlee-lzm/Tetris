#include "src/States/hpp/ConnectState.hpp"
#include "src/States/hpp/GameState.hpp"
#include "src/DEFINE.hpp"
#include <iostream>
#include <SFML/Network.hpp>
#include <thread>

namespace hgw
{
	ConnectState::ConnectState(GameDataRef _data)
	{
		this->_data = _data;
	}

	void ConnectState::Init()
	{
		_data->graphics.LoadFont("font", FONT_PATH);
		sf::Font &font = _data->graphics.GetFont("font");

		createGameText.setString("CREATE GAME");
		createGameText.setFont(font);
		createGameText.setCharacterSize(50);

		joinGameText.setString("JOIN GAME");
		joinGameText.setFont(font);
		joinGameText.setCharacterSize(50);

		localIPText.setString("Your IP: " + sf::IpAddress::getPublicAddress().toString());
		localIPText.setFont(font);
		localIPText.setCharacterSize(50);

		localPortText.setString("Your Port: _____");
		localPortText.setFont(font);
		localPortText.setCharacterSize(50);

		ipConnectText.setString("SERVER IP:");
		ipConnectText.setFont(font);
		ipConnectText.setCharacterSize(50);

		portConnectText.setString("SERVER PORT:");
		portConnectText.setFont(font);
		portConnectText.setCharacterSize(50);
		
		serverIpText.setString("|");
		serverIpText.setFont(font);
		serverIpText.setCharacterSize(50);

		serverPortText.setString("");
		serverPortText.setFont(font);
		serverPortText.setCharacterSize(50);

		waitingForConnectionText.setString("WAITING FOR CONNECTION");
		waitingForConnectionText.setFont(font);
		waitingForConnectionText.setCharacterSize(50);

		joinMatchText.setString("JOIN MATCH");
		joinMatchText.setFont(font);
		joinMatchText.setCharacterSize(50);

		createGameText.setPosition((APP_WIDTH - createGameText.getGlobalBounds().width) / 2, 300);
		joinGameText.setPosition((APP_WIDTH - joinGameText.getGlobalBounds().width) / 2, createGameText.getPosition().y + 100);
		localIPText.setPosition((APP_WIDTH - localIPText.getGlobalBounds().width) / 2, 150);
		localPortText.setPosition((APP_WIDTH - localPortText.getGlobalBounds().width) / 2, localIPText.getPosition().y + 70);

		ipConnectText.setPosition((APP_WIDTH - ipConnectText.getGlobalBounds().width) / 2, 200);
		portConnectText.setPosition((APP_WIDTH - portConnectText.getGlobalBounds().width) / 2, ipConnectText.getPosition().y + 150);
		waitingForConnectionText.setPosition((APP_WIDTH - waitingForConnectionText.getGlobalBounds().width) / 2, localPortText.getPosition().y + 70);

		serverIpText.setPosition((APP_WIDTH - serverIpText.getGlobalBounds().width) / 2, ipConnectText.getPosition().y + 50);
		serverPortText.setPosition((APP_WIDTH - serverPortText.getGlobalBounds().width) / 2, portConnectText.getPosition().y + 50);

		joinMatchText.setPosition((APP_WIDTH - joinMatchText.getGlobalBounds().width) / 2, 500);

		ipFloatRect = sf::FloatRect{ ipConnectText.getPosition().x - 20, ipConnectText.getPosition().y + 50,
							   	 ipConnectText.getGlobalBounds().width + 40, ipConnectText.getGlobalBounds().height + 50 };

		portFloatRect = sf::FloatRect{ portConnectText.getPosition().x - 20, portConnectText.getPosition().y + 50,
								 portConnectText.getGlobalBounds().width + 40, portConnectText.getGlobalBounds().height + 50 };
	}

	void ConnectState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}
			if (!isCreatingGame && !isJoiningGame)
			{
				if (_data->input.IsTextClicked(createGameText, sf::Mouse::Left, event.type, _data->window)) //create game text
				{
					isCreatingGame = true;

					_data->network.addClient("enemy");
					//start listening from other thread, cause sf::TcpListener::listen() blocks thread from which is called
					gameCreated = std::async( &NetworkManager::listenForConnection, &_data->network, sf::Socket::AnyPort, std::ref(_data->network.getTcpClient("enemy")));
					std::this_thread::sleep_for(std::chrono::milliseconds(1)); //listenForConnetction must be called first in order to get localport

					localport = _data->network._tcpServer.getLocalPort();
					localPortText.setString("Your Port: " + std::to_string(localport));

					

					waitingClock.restart();
				}
				else if (_data->input.IsTextClicked(joinGameText, sf::Mouse::Left, event.type, _data->window)) //join game text
				{
					isJoiningGame = true;
				}
			}
			else if (isJoiningGame) //join game clicked
			{
				if ((_data->input.IsTextClicked(ipConnectText, sf::Mouse::Left, event.type, _data->window) ||
					_data->input.IsIntRectHeld(sf::IntRect(ipFloatRect), sf::Mouse::Left, _data->window) ||
					_data->input.IsTextClicked(serverIpText, sf::Mouse::Left, event.type, _data->window)) && !isTypingIp) //ip to connect to text
				{
					isTypingIp = true;
					isTypingPort = false;
					cursorChanged = true;
				}
				else if ((_data->input.IsTextClicked(portConnectText, sf::Mouse::Left, event.type, _data->window) ||
						 _data->input.IsIntRectHeld(sf::IntRect(portFloatRect), sf::Mouse::Left, _data->window) || 
					   	 _data->input.IsTextClicked(serverPortText, sf::Mouse::Left, event.type, _data->window)) && !isTypingPort ) //port to connect to text
				{
					isTypingIp = false;
					isTypingPort = true;
					cursorChanged = true;
				}
				else if (_data->input.IsTextClicked(joinMatchText, sf::Mouse::Left, event.type, _data->window)) //join game text
				{
					ipToConnectTo = sf::IpAddress(ipDigitsEntered);
					portToConnectTo = std::stoi(portDigitsEntered);

					if (_data->network.addTcpSocket("enemy", ipToConnectTo, portToConnectTo))
					{
						_data->machine.AddState(StateRef(new GameState(_data, true)));
					}
				}
				
				if (event.type == sf::Event::KeyPressed)
				{
					if (isTypingIp)
					{
						char digitPressed = getPressedDigit(event, true);

						if ((event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Backspace) && ipDigitsEntered.size() > 0) //removing ip digit
						{
							isIpFullyEnterd = false;
							ipDigitsEntered.erase(ipDigitsEntered.end() - 1);
							serverIpText.setString(ipDigitsEntered);
							serverIpText.setPosition((APP_WIDTH - serverIpText.getGlobalBounds().width) / 2, serverIpText.getPosition().y); //adjust when writing
						}
						else if (ipDigitsEntered.size() < 15 && digitPressed != 'X') //adding ip digit
						{
							isIpFullyEnterd = false;
							ipDigitsEntered += digitPressed;
							serverIpText.setString(ipDigitsEntered);
							serverIpText.setPosition((APP_WIDTH - serverIpText.getGlobalBounds().width) / 2, serverIpText.getPosition().y); //adjust when writing
						}
						else if (ipDigitsEntered.size() == 15)
						{
							isIpFullyEnterd = true;
						}
					}

					if (isTypingPort)
					{
						char digitPressed = getPressedDigit(event, false);

						if ((event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Backspace) && portDigitsEntered.size() > 0) //removing ip digit
						{
							isPortFullyEnterd = false;
							portDigitsEntered.erase(portDigitsEntered.end() - 1);
							serverPortText.setString(portDigitsEntered);
							serverPortText.setPosition((APP_WIDTH - serverPortText.getGlobalBounds().width) / 2, serverPortText.getPosition().y); //adjust when writing
						}
						else if (portDigitsEntered.size() < 5 && digitPressed != 'X') //adding ip digit
						{
							isPortFullyEnterd = false;
							portDigitsEntered += digitPressed;
							serverPortText.setString(portDigitsEntered);
							serverPortText.setPosition((APP_WIDTH - serverPortText.getGlobalBounds().width) / 2, serverPortText.getPosition().y); //adjust when writing
						}
						else if (portDigitsEntered.size() == 5)
						{
							isPortFullyEnterd = true;
						}
					}
				}
			}
		}
	}

	void ConnectState::Update(float dt)
	{
		if (waitingClock.getElapsedTime().asMilliseconds() >= 1000 || cursorChanged) //dots animation/cursor animation
		{
			if (isCreatingGame)
			{
				if (dotsGoingForward) //adding dots
				{
					if (waitingDots.size() < 3)
					{
						waitingDots += ".";
					}
					else
					{
						dotsGoingForward = false;
					}
				}
				else //removing dots
				{
					if (waitingDots.size() > 0)
					{
						waitingDots.erase(waitingDots.end() - 1);
					}
					else
					{
						dotsGoingForward = true;
					}
				}
				waitingForConnectionText.setString("WAITING FOR CONNECTION" + waitingDots);
				waitingClock.restart();
			}
			else if (isJoiningGame)
			{
				if (cursorChanged || textCursor == "")
				{
					textCursor = "|";
				}
				else if (textCursor == "|")
				{
					textCursor = "";
				}

				if (isTypingIp)
				{
					serverIpText.setString(ipDigitsEntered + textCursor);
					serverPortText.setString(portDigitsEntered);
				}
				else if(isTypingPort)
				{
					serverIpText.setString(ipDigitsEntered);
					serverPortText.setString(portDigitsEntered + textCursor);
				}
				
				waitingClock.restart();
				cursorChanged = false;
			}
		}

		if (gameCreated.valid() && gameCreated.wait_for(std::chrono::microseconds(1)) == std::future_status::ready && gameCreated.get())
		{
			_data->machine.AddState(StateRef(new GameState(_data, true)));
		}

		//std::cout << "Mouse X: " << _data->input.GetMousePosition(_data->window).x << "  Y: " << _data->input.GetMousePosition(_data->window).y << std::endl;
		//std::cout << "Top Rect X: " << ipFloatRect.left << "  Top Rect Y: " << ipFloatRect.top << std::endl;
	}

	void ConnectState::Draw(float dt)
	{
		_data->window.clear();

		if (!isCreatingGame && !isJoiningGame)
		{
			_data->window.draw(createGameText);
			_data->window.draw(joinGameText);
		}
		else if (isCreatingGame)
		{
			_data->window.draw(waitingForConnectionText);
			_data->window.draw(localIPText);
			_data->window.draw(localPortText);
		}
		else if (isJoiningGame)
		{
			_data->window.draw(portConnectText);
			_data->window.draw(ipConnectText);
			_data->window.draw(serverIpText);
			_data->window.draw(serverPortText);
			_data->window.draw(joinMatchText);

		}
		
		_data->window.display();
	}

	char ConnectState::getPressedDigit(sf::Event event, bool withDot) //if X returned - no key was pressed
	{
		char keyPressed = 'X';

		switch (event.key.code)
		{
		case sf::Keyboard::Num0:
		case sf::Keyboard::Numpad0:
			keyPressed = '0';
			break;

		case sf::Keyboard::Num1:
		case sf::Keyboard::Numpad1:
			keyPressed = '1';
			break;

		case sf::Keyboard::Num2:
		case sf::Keyboard::Numpad2:
			keyPressed = '2';
			break;

		case sf::Keyboard::Num3:
		case sf::Keyboard::Numpad3:
			keyPressed = '3';
			break;

		case sf::Keyboard::Num4:
		case sf::Keyboard::Numpad4:
			keyPressed = '4';
			break;

		case sf::Keyboard::Num5:
		case sf::Keyboard::Numpad5:
			keyPressed = '5';
			break;

		case sf::Keyboard::Num6:
		case sf::Keyboard::Numpad6:
			keyPressed = '6';
			break;

		case sf::Keyboard::Num7:
		case sf::Keyboard::Numpad7:
			keyPressed = '7';
			break;

		case sf::Keyboard::Num8:
		case sf::Keyboard::Numpad8:
			keyPressed = '8';
			break;

		case sf::Keyboard::Num9:
		case sf::Keyboard::Numpad9:
			keyPressed = '9';
			break;

		case sf::Keyboard::Period:
			keyPressed = '.';
			break;
		}

		if (keyPressed == '.' && !withDot)
		{
			keyPressed = 'X';
		}

		return keyPressed;
	}
}