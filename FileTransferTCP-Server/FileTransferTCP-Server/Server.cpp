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

void Server::start(Socket& mainSocket, const int port, const FileHandler& fileHandler)
{
	mainSocket.acceptConnection(port);

	while (true)
	{
		int cmd = 0;
		int bytesReceived = recv(mainSocket.getClientSocket(), reinterpret_cast<char*>(&cmd), sizeof(int), 0);
		if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
			std::cerr << "Error in receiving command number." << std::endl;
			return;
		}

		if (cmd == EXIT) {
			break;
		}

		switch (cmd)
		{
		case GET: {
			const char* filename = mainSocket.receiveChunkedData();

			std::string pathToFile = "C:/Meine/KSE/ClientServer/FileTransferTCP/server_storage/" + std::string(filename);
			char* buffer = fileHandler.getFileContent(move(pathToFile));

			mainSocket.sendChunkedData(buffer, 10);

			delete[] buffer;
			delete[] filename;
			break;
		}
		case LIST: {
			break;
		}
		case PUT: {
			const char* filename = mainSocket.receiveChunkedData();
			const char* buffer = mainSocket.receiveChunkedData();

			std::string pathToFile = "C:/Meine/KSE/ClientServer/FileTransferTCP/server_storage/" + std::string(filename);
			fileHandler.createFile(buffer, move(pathToFile));

			mainSocket.sendResponse("File was uploaded successfully.");
			std::cout << "File '" << filename << "' was created" << std::endl;

			delete[] buffer;
			delete[] filename;
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

	mainSocket.closeConnection();
}
