#pragma once
#include <string>

class FileAnalizer {
public:

	enum class CaseSense {
		sensetive,
		insensetive
	};

	enum class SelfSufficiency {
		wholeWord,
		partWord
	};

	FileAnalizer(const std::string& path, const std::string& separators = " .,?!;:()'…–\"\t");
	unsigned int wordsCounter(const std::string& countingWord, const CaseSense& caseSense, const SelfSufficiency& selfSufficiency) const;
	uint32_t checksum32() const; 

private:
	
	std::string inputFilePath_;
	std::string separators_;
};


