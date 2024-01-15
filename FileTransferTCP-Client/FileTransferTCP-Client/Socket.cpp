#include "Socket.h"

int Socket::connect(PCWSTR serverIp, int port) {
	// Initialize Winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed" << std::endl;
		return -1;
	}

	// Client configuration
	this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}

	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	InetPton(AF_INET, serverIp, &serverAddr.sin_addr);

	// Connect to the server
	if (_WINSOCK2API_::connect(this->clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cerr << "Connect failed with error: " << WSAGetLastError() << std::endl;
		this->disconnect();
		return -1;
	}

	return 0;
}

int Socket::disconnect() {
	// Clean up
	closesocket(this->clientSocket);
	WSACleanup();
	return 0;
}

int Socket::send(const char* buffer) {
	// Send data to the server
	_WINSOCK2API_::send(this->clientSocket, buffer, (int)strlen(buffer), 0);

	// Receive the response from the server
	char rbuffer[1024];
	memset(rbuffer, 0, 1024);
	int bytesReceived = recv(this->clientSocket, rbuffer, sizeof(rbuffer), 0);
	if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
		std::cerr << "Error in receiving total size." << std::endl;
		return -1;
	}

	std::cout << "Received from server: " << rbuffer << std::endl;
	return 0;
}
