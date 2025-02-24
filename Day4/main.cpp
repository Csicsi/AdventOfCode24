#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

std::vector<std::vector<char>> getInput() {
	std::ifstream inputFile("input.txt");
	if (!inputFile) {
		std::cerr << "Error: Could not open the file!" << std::endl;
		return {};
	}
	std::vector<std::vector<char>> input;
	std::string line;
	while (std::getline(inputFile, line)) {
		input.push_back(std::vector<char>(line.begin(), line.end()));
	}
	inputFile.close();
	return input;
}

int main() {
	auto grid = getInput();
	if (grid.empty()) {
		return 1;
	}

	int height = grid.size();
	int width = grid[0].size();
	std::string word = "XMAS";
	int wordLength = word.length();
	int count = 0;

	std::vector<std::pair<int, int>> directions = {
		{-1, -1}, {-1, 0}, {-1, 1},
		{ 0, -1},          { 0, 1},
		{ 1, -1}, { 1, 0}, { 1, 1}
	};

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (const auto& dir : directions) {
				int dx = dir.first;
				int dy = dir.second;
				bool found = true;
				for (int k = 0; k < wordLength; k++) {
					int ni = i + k * dx;
					int nj = j + k * dy;

					if (ni < 0 || ni >= height || nj < 0 || nj >= width || grid[ni][nj] != word[k]) {
						found = false;
						break;
					}
				}
				if (found) {
					count++;
				}
			}
		}
	}


	std::cout << "Found " << count << " instances of " << word << std::endl;

	count = 0;

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			if (grid[i][j] != 'A') {
				continue;
			}
			char topLeft = grid[i - 1][j - 1];
			char topRight = grid[i - 1][j + 1];
			char bottomLeft = grid[i + 1][j - 1];
			char bottomRight = grid[i + 1][j + 1];
			bool leftDiagonal = ((topLeft == 'M' && bottomRight == 'S')
				|| (topLeft == 'S' && bottomRight == 'M'));
			bool rightDiagonal = ((topRight == 'M' && bottomLeft == 'S')
				|| (topRight == 'S' && bottomLeft == 'M'));
			if (leftDiagonal && rightDiagonal) {
				count++;
			}
		}
	}

	std::cout << "Found " << count << " instances of X-MAS" << std::endl;

	return 0;
}
