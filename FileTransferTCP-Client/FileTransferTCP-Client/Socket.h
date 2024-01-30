#pragma once

#include <iostream>
#include <cstdint>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <thread>

#include <vector>

#include "FileHandler.h"

class ISocket {
public:
	virtual ~ISocket(){}
	virtual int connect(PCWSTR IP, int port) = 0;
	virtual int disconnect() = 0;
	virtual int sendChunkedData(const char* data, int chunkSize) const = 0;
	virtual int sendLargeFile(std::string&& pathToFile, int chunkSize) const = 0;
	virtual int sendIntData(int num) const = 0;
	virtual int receiveLargeFile(const std::string& pathToFile, const FileHandler& fileHandler) const = 0;
	virtual char* receiveChunkedData() const = 0;
	virtual const char* receiveConfirmationFromServer() const = 0;
};

class Socket: public ISocket {
	SOCKET clientSocket;
public:
	Socket();
	Socket(const Socket&) = delete;
	Socket(Socket&&) = delete;

	int connect(PCWSTR IP, int port) override;
	int disconnect() override;
	int sendChunkedData(const char* data, int chunkSize) const override;
	int sendLargeFile(std::string&& pathToFile, int chunkSize) const override;
	int sendIntData(int num) const override;
	int receiveLargeFile(const std::string& pathToFile, const FileHandler& fileHandler) const override;
	char* receiveChunkedData() const override;
	const char* receiveConfirmationFromServer() const override;

	const SOCKET& getClientSocket() const;
};
