#pragma once

#include <iostream>
#include <vector>

#include "Socket.h"

class ICLI {
public:
	virtual ~ICLI() {};
	virtual void run(Socket& clientSocket) = 0;
};

class CLI: public ICLI {
public:
	CLI();
	CLI(const CLI&) = delete;
	CLI(CLI&&) = delete;

	void run(Socket& clientSocket) override;
};
