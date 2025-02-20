#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>

bool safelyIncreasing(const std::vector<int>& row) {
	for (int i = 0; i < row.size() - 1; ++i) {
		if (row[i] >= row[i + 1] || row[i + 1] - row[i] > 3) {
			return false;
		}
	}
	return true;
}

bool safelyDecreasing(const std::vector<int>& row) {
	for (int i = 0; i < row.size() - 1; ++i) {
		if (row[i] <= row[i + 1] || row[i] - row[i + 1] > 3) {
			return false;
		}
	}
	return true;
}

bool ProblemDampener(const std::vector<int>& row) {
	for (int i = 0; i < row.size(); ++i) {
		std::vector<int> temp = row;
		temp.erase(temp.begin() + i);
		if (safelyIncreasing(temp) || safelyDecreasing(temp)) {
			return true;
		}
	}
	return false;
}

int main() {
	std::ifstream inputFile("input.txt");
	if (!inputFile) {
		std::cerr << "Error: Could not open the file!" << std::endl;
		return 1;
	}

	std::vector<std::vector<int>> input;
	std::string line;

	while (std::getline(inputFile, line)) {
		std::stringstream ss(line);
		std::vector<int> row;
		int num;
		while (ss >> num) {
			row.push_back(num);
		}
		if (!row.empty()) {
			input.push_back(row);
		}
	}

	inputFile.close();

	int safe = 0;

	for (const auto& row : input) {
		if (safelyIncreasing(row) || safelyDecreasing(row)) {
			++safe;
		}
	}

	std::cout << "Safe reports: " << safe << std::endl;

	safe = 0;

	for (const auto& row : input) {
		if (ProblemDampener(row)) {
			++safe;
		}
	}

	std::cout << "Safe reports with dampener: " << safe << std::endl;

	return 0;
}
