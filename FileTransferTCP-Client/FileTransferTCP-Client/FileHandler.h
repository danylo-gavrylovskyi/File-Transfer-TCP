#pragma once

#include <iostream>
#include <fstream>

#include <string>

class IFileHandler {
public:
	virtual ~IFileHandler() {};

	virtual char* getFileContent(std::string&& getPathToFile) const = 0;
	virtual int createFile(const char* buffer, std::string&& pathToFile) const = 0;
	virtual int appendDataToFile(const std::string& pathToFile, const char* buffer) const = 0;
};

class FileHandler: public IFileHandler {
public:
	FileHandler();
	FileHandler(const FileHandler&) = delete;
	FileHandler(FileHandler&&) = delete;

	char* getFileContent(std::string&& getPathToFile) const override;
	int createFile(const char* buffer, std::string&& pathToFile) const override;
	int appendDataToFile(const std::string& pathToFile, const char* buffer) const override;
};
