#include "Socket.h"

Socket::Socket(){}

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

int Socket::sendIntData(int num) const {
	if (send(this->clientSocket, reinterpret_cast<const char*>(&num), sizeof(int), 0) == SOCKET_ERROR) {
		std::cerr << "Failed to send int data." << std::endl;
		return -1;
	}

	return 0;
}

int Socket::sendChunkedData(const char* data, int chunkSize) const {
	int dataSize = strlen(data);

	// Send total size first
	if (send(this->clientSocket, reinterpret_cast<const char*>(&dataSize), sizeof(int), 0) == SOCKET_ERROR) {
		std::cerr << "Failed to send total size." << std::endl;
		return -1;
	}

	if (send(clientSocket, reinterpret_cast<const char*>(&chunkSize), sizeof(int), 0) == SOCKET_ERROR) {
		std::cerr << "Failed to send chunk size." << std::endl;
		return -1;
	}

	int totalSent = 0;

	while (totalSent < dataSize) {
		int remaining = dataSize - totalSent;
		int currentChunkSize = (remaining < chunkSize) ? remaining : chunkSize;

		if (send(this->clientSocket, data + totalSent, currentChunkSize, 0) == SOCKET_ERROR) {
			std::cerr << "Failed to send chunked data." << std::endl;
			break;
		}

		totalSent += currentChunkSize;
	}

	return 0;
}

const char* Socket::receiveResponseFromServer() const {
	int size = 0;
	int bytesReceived = recv(this->clientSocket, reinterpret_cast<char*>(&size), sizeof(int), 0);
	if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
		std::cerr << "Error in receiving total size." << std::endl;
	}

	char* buffer = new char[size + 1];
	memset(buffer, 0, size);
	bytesReceived = recv(this->clientSocket, buffer, size, 0);
	if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
		std::cerr << "Error in receiving message from server." << std::endl;
	}
	buffer[size] = '\0';

	return buffer;
}

const SOCKET& Socket::getClientSocket() const {
	return this->clientSocket;
}
