#pragma once
#include <string>

class FileAnalizer {
public:
	FileAnalizer(const std::string& path);
	unsigned int wordsCounter(
		const std::string& countingWord,
		const std::string& separators = " .,?!;:()'…–\"\t") const; //счётчик слов, принимает искомое слово , чувствительность к региструи строку символов разделителей в качестве аргументов, возвращает количество найденных слов
	uint32_t checksum32() const; // возвращает 32-хбитную чексумму, рассчитанную по алгоритму checksum = word1 + word2 + … +wordN (word1..wordN – 32-хбитные слова, представляющие содержимое файла)

private:
	std::string inputFilePath_;
};


