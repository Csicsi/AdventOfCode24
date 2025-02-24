#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <regex>

std::string getInput() {
	std::ifstream inputFile("input.txt");
	if (!inputFile) {
		std::cerr << "Error: Could not open the file!" << std::endl;
		return {};
	}

	std::string line, input;

	while (std::getline(inputFile, line)) {
		std::istringstream iss(line);
		input += line;
	}

	inputFile.close();

	return input;
}

int main() {
	auto input = getInput();
	if (input.empty()) {
		return 1;
	}

	int result = 0;

	std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
	std::smatch matches;
	std::string::const_iterator searchStart(input.cbegin());
	while (std::regex_search(searchStart, input.cend(), matches, pattern)) {
		result += std::stoi(matches[1]) * std::stoi(matches[2]);
		searchStart = matches.suffix().first;
	}

	std::cout << "Result: " << result << std::endl;

	pattern = R"((do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\)))";
	bool mulEnabled = true;

	auto begin = std::sregex_iterator(input.cbegin(), input.cend(), pattern);
	auto end = std::sregex_iterator();
	result = 0;
	for (std::sregex_iterator i = begin; i != end; ++i) {
		std::smatch matches = *i;
		if (matches[1].str() == "do()") {
			mulEnabled = true;
		} else if (matches[1].str() == "don't()") {
			mulEnabled = false;
		} else if (mulEnabled) {
			result += std::stoi(matches[2]) * std::stoi(matches[3]);
		}
	}

	std::cout << "Result: " << result << std::endl;

	return 0;
}
