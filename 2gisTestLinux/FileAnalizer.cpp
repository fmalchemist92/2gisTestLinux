#include "FileAnalizer.h"
#include <fstream>
#include <iostream>

FileAnalizer::FileAnalizer(const std::string& path) :
	inputFilePath_(path){
}

unsigned int FileAnalizer::wordsCounter(const std::string& countingWord) {
	std::ifstream file(inputFilePath_, std::ios::in);
	if (!file) throw cantOpenFile("can't open file " + inputFilePath_);
	unsigned int counter(0);
	for (std::string word; file >> word;) {
		if (word == countingWord) ++counter;
	}
	return counter;
}

uint32_t FileAnalizer::checksum32() {
	std::ifstream file(inputFilePath_, std::ios::in | std::ios::binary);
	if (!file) throw cantOpenFile("can't open file " + inputFilePath_);
	uint32_t summ(0);
	while (!file.eof()) {
		uint32_t word32 = 0; // чистый буфер перед каждым считыванием
		file.read(reinterpret_cast<char*>(&word32), sizeof(word32)); //Читает по 4 байта
		summ += word32;
		//std::cout << std::hex << word32 << std::endl;
	}
	//std::cout << "summ = " << summ << std::endl;
	return summ;
}
