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
			clientSocket.sendChunkedData(filename.c_str(), 2);

			std::string pathToFolder;
			std::cout << "Enter path to folder where you want to save requested file: ";
			std::cin >> pathToFolder;

			std::string pathToFile = move(pathToFolder) + "/" + move(filename);

			const char* requestedFile = clientSocket.receiveChunkedData();
			fileHandler.createFile(requestedFile, move(pathToFile));

			delete[] requestedFile;
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
			clientSocket.sendChunkedData(move(filename).c_str(), 2);

			char* buffer = fileHandler.getFileContent(move(pathToFile));
			clientSocket.sendChunkedData(buffer, 10);
			delete[] buffer;

			std::cout << clientSocket.receiveConfirmationFromServer() << std::endl;

			break;
		}
		case DELETE_FILE: {
			std::string filename;
			std::cout << "Enter filename to delete from the server: ";
			std::cin >> filename;
			clientSocket.sendChunkedData(move(filename).c_str(), 2);

			std::cout << clientSocket.receiveConfirmationFromServer() << std::endl;

			break;
		}
		case INFO: {
			break;
		}
		default:
			break;
		}
	}
}
