#pragma once

#include <iostream>

#include "Socket.h"
#include "FileHandler.h"

class ICLI {
public:
	virtual ~ICLI() {};
	virtual void run(Socket& clientSocket, const FileHandler& fileHandler) = 0;
};

class CLI: public ICLI {
	enum Commands;
public:
	CLI();
	CLI(const CLI&) = delete;
	CLI(CLI&&) = delete;

	void run(Socket& clientSocket, const FileHandler& fileHandler) override;
};
