#pragma once

#include <filesystem>

#include <thread>
#include <vector>

#include "Socket.h"
#include "FileHandler.h"
#include "DataStreamer.h"

class IServer {
public:
	virtual ~IServer(){}

	virtual void start(Socket& serverSocket, const int port, const FileHandler& fileHandler) = 0;
	virtual void handleClient(SOCKET& clientSocket, const FileHandler& fileHandler, const DataStreamer& dataStreamer) = 0;
};

class Server: public IServer {
	enum Commands;
public:
	Server();
	Server(const Server&) = delete;
	Server(Server&&) = delete;

	void start(Socket& serverSocket, const int port, const FileHandler& fileHandler) override;
	void handleClient(SOCKET& clientSocket, const FileHandler& fileHandler, const DataStreamer& dataStreamer) override;
};
