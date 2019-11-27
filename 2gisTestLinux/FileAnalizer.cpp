#include <stdexcept>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string_view>
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
		auto beginOfWord(line.begin());
		auto it = beginOfWord;
		for (;it != line.end(); it++) {
			if (separators.find(*it) != std::string::npos) {
				if(std::equal(beginOfWord, it, countingWord.begin())) {
					++counter;
				}
				beginOfWord = it + 1;
			}
		}
		if (std::equal(beginOfWord, it, countingWord.begin())) {
			++counter;
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

