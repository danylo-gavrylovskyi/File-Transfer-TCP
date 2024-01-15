#pragma once

#include <iostream>
#include <cstdint>
#include <WinSock2.h>
#include <Ws2tcpip.h>

class ISocket {
	virtual int connect(PCWSTR IP, int port) = 0;
	virtual int disconnect() = 0;
	virtual int send(const char* buffer) = 0;
};

class Socket: public ISocket {
	SOCKET clientSocket;
public:
	int connect(PCWSTR IP, int port) override;
	int disconnect() override;
	int send(const char* buffer) override;
};
