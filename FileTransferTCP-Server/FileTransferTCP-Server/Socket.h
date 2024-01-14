#pragma once

#include <iostream>
#include <cstdint>
#include <WinSock2.h>

class Socket {
	SOCKET serverSocket;
	SOCKET clientSocket;
public:
	int acceptConnection(int port);
	void close();
	void receiveData();
};
