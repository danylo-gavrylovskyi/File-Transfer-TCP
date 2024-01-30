#include <iostream>
#include <WinSock2.h>

#include "Socket.h"
#include "Server.h"
#include "FileHandler.h"

// Linking the library needed for network communication
#pragma comment(lib, "ws2_32.lib")

int main()
{
	const int PORT = 12345;

	Socket serverSocket;
	serverSocket.startUp(PORT);

	FileHandler fileHandler;

	Server server;
	server.start(serverSocket, PORT, fileHandler);

	return 0;
}