#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

bool getInput(std::vector<int>& left, std::vector<int>& right) {
	std::ifstream inputFile("input.txt");
	if (!inputFile) {
		std::cerr << "Error: Could not open the file!" << std::endl;
		return false;
	}

	int first, second;
	while (inputFile >> first >> second) {
		left.emplace_back(first);
		right.emplace_back(second);
	}

	inputFile.close();
	return true;
}

int main() {

	std::vector<int> left, right;

	if (!getInput(left, right)) {
		return 1;
	}

	std::sort (left.begin(), left.end());
	std::sort (right.begin(), right.end());

	if (left.size() != right.size()) {
		std::cerr << "Error: The number of elements in the two vectors are not equal!" << std::endl;
		return 1;
	}

	int diff = 0;

	for  (int i = 0; i < left.size(); i++) {
		diff += std::abs(left[i] - right[i]);
	}

	std::cout << "The total distance between the two lists is: " << diff << std::endl;

	int occ, sim = 0;

	for (const auto& elem : left) {
		occ = 0;
		for (const auto& elem2 : right) {
			if (elem == elem2) {
				occ++;
			}
		}
		sim += occ * elem;
	}

	std::cout << "The similarity between the two lists is: " << sim << std::endl;

	return 0;
}
