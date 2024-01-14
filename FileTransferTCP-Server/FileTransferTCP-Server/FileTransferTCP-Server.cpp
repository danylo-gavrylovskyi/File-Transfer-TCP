#include <iostream>
#include <WinSock2.h>

#include "Socket.h"

// Linking the library needed for network communication
#pragma comment(lib, "ws2_32.lib")

int main()
{
	const int port = 12345;

	Socket serverSocket{};
	serverSocket.acceptConnection(port);
	serverSocket.receiveData();
	serverSocket.close();

	return 0;
}