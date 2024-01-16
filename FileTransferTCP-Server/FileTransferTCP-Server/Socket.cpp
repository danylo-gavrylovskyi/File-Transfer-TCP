#include "Socket.h"

Socket::Socket(){}

int Socket::acceptConnection(int port) {
	// Initialize Winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed" << std::endl;
		return 1;
	}

	// Server configuration
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->serverSocket == INVALID_SOCKET)
	{
		std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}
	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	// Bind the socket
	if (bind(this->serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
		this->close();
		return 1;
	}

	// Listen for incoming connections
	if (listen(this->serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
		this->close();
		return 1;
	}

	std::cout << "Server listening on port " << port << std::endl;

	// Accept a client connection
	this->clientSocket = accept(this->serverSocket, nullptr, nullptr);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
		this->close();
		return 1;
	}

	return 0;
}

void Socket::close() {
	// Clean up
	closesocket(this->clientSocket);
	closesocket(this->serverSocket);
	WSACleanup();
}

void Socket::receiveData() {
	// Receive data from the client
	char filename[255];
	memset(filename, 0, 255);
	int bytesReceived = recv(this->clientSocket, filename, sizeof(filename), 0);
	if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
		send(this->clientSocket, "Operation failed.", (int)strlen("Operation failed."), 0);
		std::cerr << "Error in receiving filename." << std::endl;
		return;
	}
	// Send a response back to the client
	const char* response = "Filename received successfully.";
	send(this->clientSocket, response, (int)strlen(response), 0);

	char buffer[1024];
	memset(buffer, 0, 1024);
	int bytesReceived2 = recv(this->clientSocket, buffer, sizeof(buffer), 0);
	if (bytesReceived2 == SOCKET_ERROR || bytesReceived2 == 0) {
		send(this->clientSocket, "Operation failed.", (int)strlen("Operation failed."), 0);
		std::cerr << "Error in receiving data." << std::endl;
		return;
	}

	std::string pathToFile = "C:/Meine/KSE/ClientServer/FileTransferTCP/server_storage/" + std::string(filename);
	std::ofstream outfile(move(pathToFile));
	outfile << buffer << std::endl;
	outfile.close();

	// Send a response back to the client
	response = "File was uploaded successfully.";
	send(this->clientSocket, response, (int)strlen(response), 0);
}

const SOCKET& Socket::getServerSocket() const {
	return this->serverSocket;
}

const SOCKET& Socket::getClientSocket() const {
	return this->clientSocket;
}
