#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <future>

namespace hgw
{
	class NetworkManager
	{
	public:
		NetworkManager() {};
		~NetworkManager() {};

		void addClient(std::string key);
		sf::TcpSocket& getTcpClient(std::string name);

		sf::UdpSocket& getUdpSocket(std::string name);
		sf::TcpSocket& getTcpSocket(std::string name);	

		bool addTcpSocket(std::string key, sf::IpAddress ip, unsigned short port, sf::Time timeout = sf::Time::Zero);
		bool addUdpSocket(std::string key, unsigned short port);
		
		void sendPacket(sf::Packet &packet, sf::TcpSocket &tcpSocket);
		void sendPacket(sf::Packet &packet, sf::UdpSocket &udpSocket, sf::IpAddress ip, unsigned short port);

		void recievePacket(sf::Packet &packet, sf::TcpSocket &tcpSocket);
		void recievePacket(sf::Packet &packet, sf::UdpSocket &udpSocket, sf::IpAddress ip, unsigned short port);

		bool listenForConnection(unsigned short port, sf::TcpSocket &client);

		size_t getTcpSocketsSize();
		size_t getUdpSocketsSize();
		size_t getTcpClientsSize();

		sf::TcpListener _tcpServer;
	private:
		std::map<std::string, std::unique_ptr<sf::TcpSocket>> _tcpSockets;
		std::map<std::string, std::unique_ptr<sf::UdpSocket>> _udpSockets;
		std::map<std::string, std::unique_ptr<sf::TcpSocket>> _tcpClients;
		
	};
}