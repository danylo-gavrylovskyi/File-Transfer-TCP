#pragma once

#include <iostream>
#include <cstdint>
#include <WinSock2.h>
#include <Ws2tcpip.h>

class ISocket {
	virtual int connect(PCWSTR IP, int port) = 0;
	virtual void disconnect() = 0;
	virtual void send(const char* buffer, int len) = 0;
};

class Socket: public ISocket {
	SOCKET clientSocket;
public:
	int connect(PCWSTR IP, int port) override;
	void disconnect() override;
	void send(const char* buffer, int len) override; //uint8_t* d, int size
};
