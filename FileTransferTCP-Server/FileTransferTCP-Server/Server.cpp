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
			std::cerr << "Error while receiving command number." << std::endl;
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

			mainSocket.sendFileUsingChunks(move(pathToFile), 100000000);

			delete[] filename;
			break;
		}
		case LIST: {
			std::vector<char*> splittedPath = {};
			std::string listOfFiles = "";
			const std::string PATH_TO_FOLDER = "C:/Meine/KSE/ClientServer/FileTransferTCP/server_storage";

			for (const auto& entry : std::filesystem::directory_iterator(PATH_TO_FOLDER)) {
				std::filesystem::path outfilename = entry.path();
				std::string outfilename_str = outfilename.string();
				char* filename = move(outfilename_str).data();

				char* partOfPath = strtok(filename, "\\");
				while (partOfPath != NULL) {
					partOfPath = strtok(NULL, "\\");
					splittedPath.push_back(partOfPath);
				}

				listOfFiles += splittedPath[splittedPath.size() - 2] + std::string(" ");

				splittedPath.clear();
			}

			mainSocket.sendChunkedData(move(listOfFiles).c_str(), 10);

			break;
		}
		case PUT: {
			const char* filename = mainSocket.receiveChunkedData();
			std::string pathToFile = "C:/Meine/KSE/ClientServer/FileTransferTCP/server_storage/" + std::string(filename);

			mainSocket.receiveChunkedDataToFile(move(pathToFile), fileHandler);

			mainSocket.sendChunkedData("File was uploaded successfully.", 10);
			std::cout << "File '" << filename << "' was created" << std::endl;

			delete[] filename;
			break;
		}
		case DELETE_FILE: {
			const char* filename = mainSocket.receiveChunkedData();
			std::string pathToFile = "C:/Meine/KSE/ClientServer/FileTransferTCP/server_storage/" + std::string(filename);

			if (fileHandler.deleteFile(move(pathToFile)) == 0) {
				std::cout << "File '" << filename << "' was deleted from the server storage." << std::endl;
				mainSocket.sendChunkedData("File was successfully deleted from the server storage.", 10);
			}
			else {
				std::cout << "Error occured while deleting '" << filename << "' from the server storage." << std::endl;
				mainSocket.sendChunkedData("Error while deleting file from the server storage.", 10);
			}

			delete[] filename;
			break;
		}
		case INFO: {
			const char* filename = mainSocket.receiveChunkedData();
			std::string pathToFile = "C:/Meine/KSE/ClientServer/FileTransferTCP/server_storage/" + std::string(filename);

			char* fileInfo = fileHandler.getFileInfo(move(pathToFile));
			mainSocket.sendChunkedData(fileInfo, 10);

			delete[] fileInfo;
			delete[] filename;
			break;
		}
		default:
			break;
		}
	}

	mainSocket.closeConnection();
}
