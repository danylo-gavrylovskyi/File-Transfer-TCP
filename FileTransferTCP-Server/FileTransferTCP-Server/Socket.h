#pragma once

#include <iostream>
#include <fstream> 
#include <cstdint>
#include <WinSock2.h>

#include "FileHandler.h"

class ISocket {
public:
	virtual ~ISocket() {}

	virtual int createServerSocket(int port) = 0;
	virtual SOCKET& acceptConnection() = 0;
	virtual int closeConnection() = 0;
};

class Socket: public ISocket {
public:
	Socket();
	Socket(const Socket&) = delete;
	Socket(Socket&&) = delete;

	int createServerSocket(int port) override;
	SOCKET& acceptConnection() override;
	int closeConnection() override;
};
