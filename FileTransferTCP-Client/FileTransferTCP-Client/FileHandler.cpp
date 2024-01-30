#include "FileHandler.h"

FileHandler::FileHandler(){}

char* FileHandler::getFileContent(std::string&& pathToFile) const
{
	FILE* file = fopen(move(pathToFile).c_str(), "rb");
	if (!file)
	{
		std::cerr << "Error while reading the file\n";
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = new char[size + 1];
	fread(buffer, size, 1, file);
	buffer[size] = '\0';

	fclose(file);

	return buffer;
}

int FileHandler::appendDataToFile(const std::string& pathToFile, const char* buffer) const
{
	std::ofstream file;
	file.open(pathToFile, std::ios::out | std::ios::app);
	if (file.fail())
		throw std::ios_base::failure(std::strerror(errno));

	file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

	file << buffer;
	file.close();
}

int FileHandler::createFile(const char* buffer, std::string&& pathToFile) const
{
	std::ofstream outfile(move(pathToFile));
	outfile << buffer << std::endl;
	outfile.close();

	return 0;
}
