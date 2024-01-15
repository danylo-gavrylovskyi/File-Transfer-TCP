#include "CLI.h"

void CLI::run(Socket clientSocket)
{
	while (true) {
		int cmd;
		std::cout << "\nChoose command:\n\t0. Exit\n\t1. GET <filename>: Request a specific file from the server.\n\t";
		std::cout << "2. LIST: Request a list of available files on the server.\n\t";
		std::cout << "3. PUT <filename>: Upload a file to the server.\n\t";
		std::cout << "4. DELETE <filename>: Request the server to delete a specific file.\n\t";
		std::cout << "5. INFO <filename>: Retrieve information about a specific file from the server.\n\t>> ";
		std::cin >> cmd;

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
			char pathToFile[255];
			std::cout << "Enter filename: ";
			std::cin >> pathToFile;

			FILE* file = fopen(pathToFile, "rb");
			if (!file)
			{
				std::cout << "Error while reading the file\n";
				break;
			}

			fseek(file, 0, SEEK_END);
			long size = ftell(file);
			fseek(file, 0, SEEK_SET);

			char* buffer = new char[size + 1];
			fread(buffer, size, 1, file);
			buffer[size] = '\0';

			fclose(file);
			clientSocket.send(buffer);
			delete[] buffer;

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
