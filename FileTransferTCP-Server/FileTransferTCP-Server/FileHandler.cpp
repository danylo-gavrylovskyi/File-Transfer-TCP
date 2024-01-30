#include "FileHandler.h"

FileHandler::FileHandler(){}

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
