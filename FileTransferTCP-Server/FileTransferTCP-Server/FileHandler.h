#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

#include <string>

class IFileHandler {
public:
	virtual ~IFileHandler() {};
	virtual char* getFileContent(std::string&& pathToFile) const = 0;
	virtual int createFile(const char* buffer, std::string&& pathToFile) const = 0;
	virtual int deleteFile(const std::string& pathToFile) const = 0;
	virtual char* getFileInfo(std::string&& pathToFile) const = 0;
};

class FileHandler : public IFileHandler {
public:
	FileHandler();
	FileHandler(const FileHandler&) = delete;
	FileHandler(FileHandler&&) = delete;

	char* getFileContent(std::string&& getPathToFile) const override;
	int createFile(const char* buffer, std::string&& pathToFile) const override;
	int deleteFile(const std::string& pathToFile) const override;
	char* getFileInfo(std::string&& pathToFile) const override;
};
