#include <stdexcept>
#include <fstream>
#include <algorithm>
#include "FileAnalizer.h"

FileAnalizer::FileAnalizer(const std::string& path, const std::string& separators) :
	inputFilePath_(path),
	separators_(separators){
}


unsigned int FileAnalizer::wordsCounter(std::string countingWord, const CaseSense& caseSense, const SelfSufficiency& selfSufficiency) const {
	std::ifstream file(inputFilePath_, std::ios::in);
	if (!file) throw std::runtime_error("can't open file " + inputFilePath_);
	unsigned int counter(0);
	std::string line;
	if (caseSense == CaseSense::insensetive) {
		std::transform(countingWord.begin(), countingWord.end(), countingWord.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}
	auto len = countingWord.end() - countingWord.begin();
	while (std::getline(file, line)) {
		if (caseSense == CaseSense::insensetive) {
			std::transform(line.begin(), line.end(), line.begin(),
				[](unsigned char c) { return std::tolower(c); });
		}
		for (auto it = line.begin(); len <= (line.end() - it);) {
			if (std::equal(countingWord.begin(), countingWord.end(), it)) {
				if (selfSufficiency == SelfSufficiency::wholeWord) {
					if  ((it == line.begin() || separators_.find(*(it - 1)) != std::string::npos )			 // либо слово в начале строки, либо слову предшествует разделитель
						&&																					 // вместе условие "отдельно стоящего" слова
						((it + len == line.end()) || separators_.find(*(it + len)) != std::string::npos) ) { // либо слово в концу строки, либо за ним следует разделитель
						++counter;
						it += len;
					}
					else {
						++it;
					}
				}
				else {
					++counter;
					it += len;
				}
			}
			else {
				++it;
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

