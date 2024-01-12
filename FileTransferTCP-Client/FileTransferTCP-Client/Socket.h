#pragma once

#include <iostream>
#include <cstdint>
#include <WinSock2.h>
#include <Ws2tcpip.h>

class Socket {
	SOCKET clientSocket;
public:
	Socket();

	int connect(PCWSTR IP, int port);
	void disconnect();
	void send(uint8_t* d, int size);
};
