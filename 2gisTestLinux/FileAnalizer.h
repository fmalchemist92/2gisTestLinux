#pragma once
#include <string>
#include <stdexcept>

class cantOpenFile : public std::runtime_error{
	using runtime_error::runtime_error;
};

class FileAnalizer {
public:
	FileAnalizer(const std::string& path);
	unsigned int wordsCounter(const std::string& countingWord);
	uint32_t checksum32();
private:
	std::string inputFilePath_;
};

