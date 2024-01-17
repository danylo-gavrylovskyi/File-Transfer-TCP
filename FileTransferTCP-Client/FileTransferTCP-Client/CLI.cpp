#include "CLI.h"

CLI::CLI(){}

void CLI::run(Socket& clientSocket)
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

		if (cmd == 0) break;

		switch (cmd)
		{
		case 1: {
			break;
		}
		case 2: {
			break;
		}
		case 3: {
			std::string pathToFile;
			std::cout << "Enter path to file: ";
			std::cin >> pathToFile;

			std::string filename;
			std::cout << "Enter filename to be created on the server: ";
			std::cin >> filename;
			clientSocket.sendChunkedData(move(filename).c_str(), 2);

			FILE* file = fopen(move(pathToFile).c_str(), "rb");
			if (!file)
			{
				std::cerr << "Error while reading the file\n";
				break;
			}

			fseek(file, 0, SEEK_END);
			long size = ftell(file);
			fseek(file, 0, SEEK_SET);

			char* buffer = new char[size + 1];
			fread(buffer, size, 1, file);
			buffer[size] = '\0';

			fclose(file);
			clientSocket.sendChunkedData(buffer, 10);
			delete[] buffer;

			std::cout << clientSocket.receiveResponseFromServer() << std::endl;

			break;
		}
		case 4: {
			break;
		}
		case 5: {
			break;
		}
		default:
			break;
		}
	}
}
