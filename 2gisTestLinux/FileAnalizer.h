#pragma once
#include <string>

class FileAnalizer {
public:
	FileAnalizer(const std::string& path);
	unsigned int wordsCounter(const std::string& countingWord, const std::string& separators = " .,?!;:()'…–\"\t") const; //функция чувствительна к регистру
	uint32_t checksum32() const; 

private:
	std::string inputFilePath_;
};


