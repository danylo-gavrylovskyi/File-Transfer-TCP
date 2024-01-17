#pragma once

#include "Socket.h"
#include "FileHandler.h"

class IServer {
public:
	virtual ~IServer(){}
	virtual void start(Socket& mainSocket, const int port, const FileHandler& fileHandler) = 0;
};

class Server: public IServer {
	enum Commands;
public:
	Server();
	Server(const Server&) = delete;
	Server(Server&&) = delete;

	void start(Socket& mainSocket, const int port, const FileHandler& fileHandler) override;
};
