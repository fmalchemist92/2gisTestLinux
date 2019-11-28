#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include "FileAnalizer.h"
#include <chrono>

namespace po = boost::program_options;

int main(int ac, char* av[]) {
	po::options_description desc("General options");
	std::string task_type;
	desc.add_options()
		("help,h", "Show help")
		("mode,m", po::value<std::string>(&task_type), "Select mode: words, checksum");
	po::options_description words_desc("words counter mode options");
	words_desc.add_options()
		("file,f", po::value<std::string>()->required(), "input file path")
		("word,v", po::value<std::string>()->required(), "counting word");
	po::options_description checksum_desc("checksum mode options");
	checksum_desc.add_options()
		("file,f", po::value<std::string>()->required(), "input file path");
	po::variables_map vm;
	try {
		po::parsed_options parsed = po::command_line_parser(ac, av).options(desc).allow_unregistered().run();
		po::store(parsed, vm);
		po::notify(vm);
		if (task_type == "words") {
			desc.add(words_desc);
			po::store(po::parse_command_line(ac, av, desc), vm);
			po::notify(vm);
			FileAnalizer FA(vm["file"].as<std::string>());
			auto start = std::chrono::system_clock::now();
			std::cout << FA.wordsCounter(vm["word"].as<std::string>(),FileAnalizer::CaseSense::sensetive,FileAnalizer::SelfSufficiency::wholeWord) << std::endl;
			auto end = std::chrono::system_clock::now();
			//------------------------------
			int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
				(end - start).count();
			time_t end_time = std::chrono::system_clock::to_time_t(end);

			std::cout << "Time: " << elapsed_seconds << "ms\n";
		}
		else if (task_type == "checksum") {
			desc.add(checksum_desc);
			po::store(po::parse_command_line(ac, av, desc), vm);
			po::notify(vm);
			FileAnalizer FA(vm["file"].as<std::string>());
			std::cout << FA.checksum32() << std::endl;
		}
		else {
			desc.add(words_desc).add(checksum_desc);
			std::cout << desc << std::endl;
		}
	}
	catch (std::exception & ex) {
		std::cout 
			<< ex.what() << std::endl
			<< desc << std::endl;
	}
}