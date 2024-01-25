#pragma once

#include <iostream>
#include <fstream> 
#include <cstdint>
#include <WinSock2.h>

#include "FileHandler.h"

class ISocket {
public:
	virtual ~ISocket() {}
	virtual int acceptConnection(int port) = 0;
	virtual int closeConnection() = 0;
	virtual const char* receiveChunkedData() const = 0;
	virtual int receiveLargeFile(const std::string& pathToFile, const FileHandler& fileHandler) const = 0;
	virtual int sendChunkedData(const char* data, int chunkSize) const = 0;
	virtual int sendResponse(const char* text) const = 0;
};

class Socket: public ISocket {
	SOCKET serverSocket;
	SOCKET clientSocket;
public:
	Socket();
	Socket(const Socket&) = delete;
	Socket(Socket&&) = delete;

	int acceptConnection(int port) override;
	int closeConnection() override;
	const char* receiveChunkedData() const override;
	int receiveLargeFile(const std::string& pathToFile, const FileHandler& fileHandler) const override;
	int sendChunkedData(const char* data, int chunkSize) const override;
	int sendResponse(const char* text) const override;

	const SOCKET& getServerSocket() const;
	const SOCKET& getClientSocket() const;
};
