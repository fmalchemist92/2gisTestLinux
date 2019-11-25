#include <string>
#include <iostream>
#include <fstream>
//#include <boost/program_options.hpp>
#include "FileAnalizer.h"

//namespace po = boost::program_options;

void showHelp() {
	std::string line;
	std::ifstream help("help.txt");
	if (help.is_open()) {
		while (getline(help, line)) {
			std::cout << line << std::endl;
		}
	}
	else std::cout << "Unable to open file help.txt";
}

int main(int argc, char* argv[]) {
	std::string input_file_name;
	enum mode {
		help,
		words,
		checksum
	};
	 mode currentMode = mode::help;
	 std::string path;
	 std::string word;
	//считывание аргументов коммандной строки
	for (int i = 1; i < argc; i++) {
		if ((!strcmp(argv[i], "-h"))) {
			currentMode = mode::help;
			break;
		}
		if ((!strcmp(argv[i], "-m")) && (i + 1 < argc)) {
			if (i + 1 < argc) {
				++i;
			}
			else {
				std::cout << "you need to whrite mode name after -m, try -h for help" << std::endl;
				exit(-1);
			}
			if (!strcmp(argv[i], "words")) {
				currentMode = mode::words;
			}
			else if (!strcmp(argv[i], "checksum")) {
				currentMode = mode::checksum;
				break;
			}
			else {
				std::cout << "unknown mode, try -h for help" << std::endl;
				exit(-1);
			}
		}
		if (!strcmp(argv[i], "-f")) {
			if (i + 1 < argc) {
				path = argv[++i];
			}
			else {
				std::cout << "you need to whrite path after -f, try -h for help" << std::endl;
				exit(-1);
			}
		}
		if (!strcmp(argv[i], "-v") && currentMode == mode::words) {
			if (i + 1 < argc) {
				word = argv[++i];
			}
			else {
				std::cout << "you need to whrite word after -v, try -h for help" << std::endl;
				exit(-1);
			}
			
		}
	}
	switch (currentMode) {
	case help:
		showHelp();
		break;
	case words:
		try {
			FileAnalizer F1(path);
			std::cout << F1.wordsCounter(word) << std::endl;
		}
		catch (cantOpenFile exept) {
			std::cout << exept.what();
		}
		break;
	case checksum:
		try {
			FileAnalizer F1(path);
			std::cout << F1.checksum32() << std::endl;
		}
		catch (cantOpenFile exept) {
			std::cout << exept.what();
		}
		break;
	}
}