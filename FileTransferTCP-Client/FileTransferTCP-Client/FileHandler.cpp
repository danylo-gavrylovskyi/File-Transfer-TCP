#include "FileHandler.h"

FileHandler::FileHandler(){}

int FileHandler::appendDataToFile(const std::string& pathToFile, const char* buffer) const
{
	std::ofstream file;
	file.open(pathToFile, std::ios::out | std::ios::app);
	if (file.fail()) {
		throw std::ios_base::failure(std::strerror(errno));
		return -1;
	}

	file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

	file << buffer;
	file.close();
	return 0;
}
