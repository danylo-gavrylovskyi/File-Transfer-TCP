#include <iostream>
#include <WinSock2.h>

#include "Socket.h"
#include "Server.h"
#include "FileHandler.h"

// Linking the library needed for network communication
#pragma comment(lib, "ws2_32.lib")

int main()
{
	const int port = 12345;

	Socket serverSocket;
	FileHandler fileHandler;

	Server server;
	server.start(serverSocket, port, fileHandler);

	return 0;
}