#include "FileAnalizer.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

FileAnalizer::FileAnalizer(const std::string& path) :
	inputFilePath_(path){
}

unsigned int FileAnalizer::wordsCounter(const std::string& countingWord) const { 
	std::ifstream file(inputFilePath_, std::ios::in);
	if (!file) throw std::runtime_error("can't open file " + inputFilePath_);
	unsigned int counter(0);
	for (std::string word; file >> word;) {
		if (word == countingWord) ++counter;
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

