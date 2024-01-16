#pragma once

#include <iostream>
#include <fstream> 
#include <cstdint>
#include <WinSock2.h>

class ISocket {
public:
	virtual ~ISocket() {}
	virtual int acceptConnection(int port) = 0;
	virtual void close() = 0;
	virtual void receiveData() = 0;
};

class Socket: public ISocket {
	SOCKET serverSocket;
	SOCKET clientSocket;
public:
	Socket();
	Socket(const Socket&) = delete;
	Socket(Socket&&) = delete;

	int acceptConnection(int port) override;
	void close() override;
	void receiveData() override;

	const SOCKET& getServerSocket() const;
	const SOCKET& getClientSocket() const;
};
