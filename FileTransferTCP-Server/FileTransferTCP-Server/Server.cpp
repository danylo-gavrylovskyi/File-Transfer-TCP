#include "Server.h"

Server::Server(){}

enum Server::Commands {
	EXIT,
	GET,
	LIST,
	PUT,
	DELETE_FILE,
	INFO
};

void Server::start(Socket& mainSocket, const int port)
{
	mainSocket.acceptConnection(port);

	while (true)
	{
		char cmdChar[1];
		int bytesReceived = recv(mainSocket.getClientSocket(), cmdChar, sizeof(cmdChar), 0);
		if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
			send(mainSocket.getClientSocket(), "Operation failed.", (int)strlen("Operation failed."), 0);
			std::cerr << "Error in receiving filename." << std::endl;
			return;
		}

		int cmd = cmdChar[0] - '0';

		if (cmd == EXIT) {
			break;
		}

		switch (cmd)
		{
		case GET: {
			break;
		}
		case LIST: {
			break;
		}
		case PUT: {
			break;
		}
		case DELETE_FILE: {
			break;
		}
		case INFO: {
			break;
		}
		default:
			break;
		}
	}

	mainSocket.close();
}
