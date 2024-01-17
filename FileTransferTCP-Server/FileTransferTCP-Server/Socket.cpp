#include "Socket.h"

Socket::Socket(){}

int Socket::acceptConnection(int port) {
	// Initialize Winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed" << std::endl;
		return -1;
	}

	// Server configuration
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->serverSocket == INVALID_SOCKET)
	{
		std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}
	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	// Bind the socket
	if (bind(this->serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
		this->closeConnection();
		return -1;
	}

	// Listen for incoming connections
	if (listen(this->serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
		this->closeConnection();
		return -1;
	}

	std::cout << "Server listening on port " << port << std::endl;

	// Accept a client connection
	this->clientSocket = accept(this->serverSocket, nullptr, nullptr);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
		this->closeConnection();
		return -1;
	}

	return 0;
}

int Socket::closeConnection() {
	// Clean up
	closesocket(this->clientSocket);
	closesocket(this->serverSocket);
	WSACleanup();
	return 0;
}

const char* Socket::receiveChunkedData() const {
	int totalSize = 0;
	int bytesReceived = recv(this->clientSocket, reinterpret_cast<char*>(&totalSize), sizeof(int), 0);
	if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
		std::cerr << "Error in receiving total size." << std::endl;
	}

	int chunkSize = 0;
	bytesReceived = recv(this->clientSocket, reinterpret_cast<char*>(&chunkSize), sizeof(int), 0);
	if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
		std::cerr << "Error in receiving chunk size." << std::endl;
	}

	char* assembledData = new char[totalSize + 1];
	int totalReceived = 0;

	while (totalReceived < totalSize) {
		char* buffer = new char[chunkSize];
		int bytesReceived = recv(this->clientSocket, buffer, sizeof(buffer), 0);

		if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
			std::cerr << "Error in receiving chunked data." << std::endl;
			break;
		}

		memcpy(assembledData + totalReceived, buffer, bytesReceived);
		totalReceived += bytesReceived;
	}

	assembledData[totalReceived] = '\0';
	std::cout << "Assembled data on the server: " << assembledData << std::endl;

	return assembledData;
}

int Socket::sendResponse(const char* text) const {
	int textSize = strlen(text);
	if (send(this->clientSocket, reinterpret_cast<const char*>(&textSize), sizeof(int), 0) == SOCKET_ERROR) {
		std::cerr << "Failed to send total size." << std::endl;
		return -1;
	}

	if (send(this->clientSocket, text, (int)strlen(text), 0) == SOCKET_ERROR) {
		std::cerr << "Failed to send response to client." << std::endl;
		return -1;
	}

	return 0;
}

const SOCKET& Socket::getServerSocket() const {
	return this->serverSocket;
}

const SOCKET& Socket::getClientSocket() const {
	return this->clientSocket;
}
