#include "Socket.h"

int Socket::connect(PCWSTR serverIp, int port) {
	// Initialize Winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed" << std::endl;
		return 1;
	}

	// Client configuration
	this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
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
		return 1;
	}

	return 0;
}

void Socket::disconnect() {
	// Clean up
	closesocket(this->clientSocket);
	WSACleanup();
}

void Socket::send(const char* buffer, int len) {
	// Send data to the server
	const char* message = "Hello, server! How are you?";
	_WINSOCK2API_::send(this->clientSocket, message, (int)strlen(message), 0);

	// Receive the response from the server
	char rbuffer[1024];
	memset(rbuffer, 0, 1024);
	int bytesReceived = recv(this->clientSocket, rbuffer, sizeof(buffer), 0);
	if (bytesReceived > 0)
	{
		std::cout << "Received from server: " << buffer << std::endl;
	}
}
