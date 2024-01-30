#pragma once

#include <iostream>
#include <fstream>

#include <string>

class IFileHandler {
public:
	virtual ~IFileHandler() {};

	virtual int appendDataToFile(const std::string& pathToFile, const char* buffer) const = 0;
};

class FileHandler: public IFileHandler {
public:
	FileHandler();
	FileHandler(const FileHandler&) = delete;
	FileHandler(FileHandler&&) = delete;

	int appendDataToFile(const std::string& pathToFile, const char* buffer) const override;
};
