#pragma once

#include "Socket.h"

class IServer {
public:
	virtual ~IServer(){}
	virtual void start(Socket& mainSocket, const int port) = 0;
};

class Server: public IServer {
	enum Commands;
public:
	Server();
	Server(const Server&) = delete;
	Server(Server&&) = delete;

	void start(Socket& mainSocket, const int port) override;
};
