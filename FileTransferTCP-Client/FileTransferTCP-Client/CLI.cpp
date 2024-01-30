#include "CLI.h"

CLI::CLI(){}

enum CLI::Commands {
	EXIT,
	GET,
	LIST,
	PUT,
	DELETE_FILE,
	INFO
};

void CLI::run(Socket& clientSocket, const FileHandler& fileHandler)
{
	while (true) {
		int cmd;
		std::cout << "\nChoose command:\n\t0. Exit\n\t1. GET <filename>: Request a specific file from the server.\n\t";
		std::cout << "2. LIST: Request a list of available files on the server.\n\t";
		std::cout << "3. PUT <filename>: Upload a file to the server.\n\t";
		std::cout << "4. DELETE <filename>: Request the server to delete a specific file.\n\t";
		std::cout << "5. INFO <filename>: Retrieve information about a specific file from the server.\n\t>> ";
		std::cin >> cmd;

		clientSocket.sendIntData(cmd);

		if (cmd == EXIT) break;

		switch (cmd)
		{
		case GET: {
			std::string filename;
			std::cout << "Enter filename to get from the server: ";
			std::cin >> filename;
			clientSocket.sendChunkedData(filename.c_str(), 10);

			std::string pathToFolder;
			std::cout << "Enter path to folder where you want to save requested file: ";
			std::cin >> pathToFolder;

			std::string pathToFile = move(pathToFolder) + "/" + filename;

			if (clientSocket.receiveChunkedDataToFile(move(pathToFile), fileHandler) == 0) {
				std::cout << "File " << filename << " was created." << std::endl;
			}

			break;
		}
		case LIST: {
			const char* listOfFiles = clientSocket.receiveChunkedData();

			std::cout << "List of files available on the server:" << std::endl;
			for (char i = 0; i < strlen(listOfFiles); i++)
			{
				if (listOfFiles[i] == ' ') std::cout << std::endl;
				else std::cout << listOfFiles[i];
			}
			std::cout << std::endl;

			delete[] listOfFiles;
			break;
		}
		case PUT: {
			std::string pathToFile;
			std::cout << "Enter path to file: ";
			std::cin >> pathToFile;

			std::string filename;
			std::cout << "Enter filename to be created on the server: ";
			std::cin >> filename;

			clientSocket.sendChunkedData(move(filename).c_str(), 10);
			clientSocket.sendFileUsingChunks(move(pathToFile), 100000000);

			std::cout << clientSocket.receiveChunkedData() << std::endl;

			break;
		}
		case DELETE_FILE: {
			std::string filename;
			std::cout << "Enter filename to delete from the server: ";
			std::cin >> filename;
			clientSocket.sendChunkedData(move(filename).c_str(), 2);

			std::cout << clientSocket.receiveChunkedData() << std::endl;

			break;
		}
		case INFO: {
			std::string filename;
			std::cout << "Enter filename to get info about from the server: ";
			std::cin >> filename;
			clientSocket.sendChunkedData(move(filename).c_str(), 2);

			char* fileInfo = clientSocket.receiveChunkedData();
			std::vector<char*> splittedFileInfo = {};

			char* fileInfoPart = strtok(fileInfo, ";");
			while (fileInfoPart != NULL) {
				splittedFileInfo.push_back(fileInfoPart);
				fileInfoPart = strtok(NULL, ";");
			}

			std::cout << "Size       : " << splittedFileInfo[0] << " bytes" << std::endl;
			std::cout << "Created    : " << splittedFileInfo[1];
			std::cout << "Modified   : " << splittedFileInfo[2];

			delete[] fileInfo;
			break;
		}
		default:
			break;
		}
	}
}
