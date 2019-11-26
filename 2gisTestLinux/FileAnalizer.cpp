#include <stdexcept>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "FileAnalizer.h"

FileAnalizer::FileAnalizer(const std::string& path) :
	inputFilePath_(path){
}

unsigned int FileAnalizer::wordsCounter(const std::string& countingWord, const std::string& separators) const {
	std::ifstream file(inputFilePath_, std::ios::in);
	if (!file) throw std::runtime_error("can't open file " + inputFilePath_);
	unsigned int counter(0);
	std::string line;
	while (std::getline(file, line)) {
		size_t beginOfWord(0);
		for (size_t i = 0; i < line.length(); ++i) {
			if (separators.find(line[i]) != std::string::npos) {
				if (line.substr(beginOfWord, i - beginOfWord) == countingWord) {
					++counter;
				}
				beginOfWord = i + 1;
			}
		}
	}
	return counter;
}

uint32_t FileAnalizer::checksum32() const { 
	std::ifstream file(inputFilePath_, std::ios::in | std::ios::binary);
	if (!file) throw std::runtime_error("can't open file " + inputFilePath_);
	uint32_t checksum = 0;
	unsigned shift = 0;
	for (uint32_t ch = file.get(); file; ch = file.get()) {
		checksum += (ch << shift);
		shift += 8;
		if (shift == 32) {
			shift = 0;
		}
	}
	return checksum;
}

