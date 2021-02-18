#include "src/GameEngine/hpp/NetworkManager.hpp"

namespace hgw
{
	void NetworkManager::addClient(std::string key)
	{
		_tcpClients[key] = std::make_unique<sf::TcpSocket>();
	}

	sf::TcpSocket& NetworkManager::getTcpClient(std::string name)
	{
		return *_tcpClients[name];
	}

	sf::TcpSocket& NetworkManager::getTcpSocket(std::string name)
	{
		return *_tcpSockets[name];
	}

	sf::UdpSocket& NetworkManager::getUdpSocket(std::string name)
	{
		return *_udpSockets[name];
	}

	bool NetworkManager::addTcpSocket(std::string key, sf::IpAddress ip, unsigned short port, sf::Time timeout)
	{
		_tcpSockets[key] = std::make_unique<sf::TcpSocket>();
		if (_tcpSockets[key]->connect(ip, port, timeout) != sf::Socket::Done)
		{
			std::cout << "[tcp socket] connection error" << std::endl;
			return false;
		}

		std::cout << "[tcp socket] connected successfully" << std::endl;
		return true;
	}

	bool NetworkManager::addUdpSocket(std::string key, unsigned short port)
	{
		_udpSockets[key] = std::make_unique<sf::UdpSocket>();
		if (_udpSockets[key]->bind(port) != sf::Socket::Done)
		{
			std::cout << "[udp socket] binding error" << std::endl;
			return false;
		}

		std::cout << "[tcp socket] binded successfully" << std::endl;
		return true;
	}

	void NetworkManager::sendPacket(sf::Packet &packet, sf::TcpSocket &tcpSocket)
	{
		if (tcpSocket.send(packet) != sf::Socket::Done)
		{
			std::cout << "[tcp socket] packet not sent" << std::endl;
		}
	}

	void NetworkManager::sendPacket(sf::Packet &packet, sf::UdpSocket &udpSocket, sf::IpAddress ip, unsigned short port)
	{
		if (udpSocket.send(packet, ip, port) != sf::Socket::Done)
		{
			std::cout << "[udp socket] packet not sent" << std::endl;
		}
	}

	void NetworkManager::recievePacket(sf::Packet &packet, sf::TcpSocket &tcpSocket)
	{
		if (tcpSocket.receive(packet) != sf::Socket::Done)
		{
			std::cout << "[tcp socket] packet not recieved" << std::endl;
		}
	}

	void NetworkManager::recievePacket(sf::Packet &packet, sf::UdpSocket &udpSocket, sf::IpAddress ip, unsigned short port)
	{
		if (udpSocket.receive(packet, ip, port) != sf::Socket::Done)
		{
			std::cout << "[udp socket] packet not recieved" << std::endl;
		}	
	}
	
	bool NetworkManager::listenForConnection(unsigned short port, sf::TcpSocket &client)
	{
		if (_tcpServer.listen(port) != sf::Socket::Done)
		{
			std::cout << "[server] Error Ocurred while listening to " << _tcpServer.getLocalPort() << std::endl;
			return false;
		}

		if (_tcpServer.accept(client) != sf::Socket::Done)
		{
			std::cout << "[server] Error Ocurred while connecting to client" << std::endl;
			return false;
		}

		std::cout << "[server] Connection accepted successfully" << std::endl;
		std::cout << client.getRemoteAddress() << std::endl;
		return true;
	}

	size_t NetworkManager::getTcpClientsSize()
	{
		return _tcpClients.size();
	}

	size_t NetworkManager::getTcpSocketsSize()
	{
		return _tcpSockets.size();
	}

	size_t NetworkManager::getUdpSocketsSize()
	{
		return _udpSockets.size();
	}
}