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

int FileHandler::createFile(const char* buffer, std::string&& pathToFile) const
{
	std::ofstream outfile(move(pathToFile));
	outfile << buffer << std::endl;
	outfile.close();

	return 0;
}

int FileHandler::deleteFile(const std::string& pathToFile) const
{
	if (std::filesystem::remove(pathToFile)) return 0;
	else return -1;
}

char* FileHandler::getFileInfo(std::string&& pathToFile) const
{
	char* fileInfo = new char[255];
	
	struct stat fInfo;
	if (stat(move(pathToFile).c_str(), &fInfo) != 0) {
		std::cerr << "Error: " << strerror(errno) << '\n';
	}

	sprintf(fileInfo, "%lld", (long long)fInfo.st_size);
	strcat(fileInfo, ";");
	strcat(fileInfo, std::ctime(&fInfo.st_ctime));
	strcat(fileInfo, ";");
	strcat(fileInfo, std::ctime(&fInfo.st_mtime));

	return fileInfo;
}
