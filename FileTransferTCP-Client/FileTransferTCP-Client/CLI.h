#pragma once

#include <iostream>

#include "Socket.h"

class ICLI {
	virtual void run(Socket clientSocket) = 0;
};

class CLI: public ICLI {
public:
	void run(Socket clientSocket) override;
};
