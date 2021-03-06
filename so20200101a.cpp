#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <sstream>

const std::string fileNameBig{ "r:\\file1.txt" };
const std::string fileNameSmall{ "r:\\file2.txt" };
const std::string fileNameResult{ "r:\\result.txt" };

// Code to generate all combinations
void generateCombinations(int N, int K, std::ostream& os)
{
	std::string bitmask(K, 1); 
	bitmask.resize(N, 0); 
	do {
		for (int i = 0; i < N; ++i)
		{
			if (bitmask[i]) os << " " << i+1;
		}
		os << "\n";
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}

// Create Test Files
void createTestFiles() {
	// Open output files and check, if they are open
	if (std::ofstream ofsBig(fileNameBig), ofsSmall(fileNameSmall); ofsBig && ofsSmall) {
		generateCombinations(10, 5, ofsBig);
		generateCombinations(5, 3, ofsSmall);
	}
}

int main() {

	// Create test files with given combinations
	createTestFiles();

	// Open input files and check, if bot could be opened and are ok
	if (std::ifstream ifsBig(fileNameBig), ifsSmall(fileNameSmall); ifsBig && ifsSmall) {

		// Open the output file and checked, if it could be opened and is ok
		if (std::ofstream ofsResult(fileNameResult); ofsResult) {

			// In this vector, we will store the combinations from the bigger file
			std::vector<std::vector<int>> vBig{};

			// Read all lines, line by line from that file
			for (std::string line{}; std::getline(ifsBig, line); ) {
				// Put the line in a istringstream
				std::istringstream iss(line);

				// Do an inplace construction of a std::vector<int> with its range constructor,
				// The range constructor will extract all intgers form the iss
				vBig.emplace_back(std::vector(std::istream_iterator<int>(iss), {}));
			}

			// In this vector, we will store the combinations from the smaller file
			std::vector<std::vector<int>> vSmall{};

			// Read all lines, line by line from that file
			for (std::string line{}; std::getline(ifsSmall, line); ) {

				// Put the line in a istringstream
				std::istringstream iss(line);

				// Do an inplace construction of a std::vector<int> with its range constructor,
				// The range constructor will extract all intgers form the iss
				vSmall.emplace_back(std::vector(std::istream_iterator<int>(iss), {}));
			}

			// Here we will store the resulting combinations
			std::vector<std::vector<int>> result{};

			// We use a std::algorithm, to copy only those combinations to the result, which fulfil your condition
			std::copy_if(vBig.begin(), vBig.end(), std::back_inserter(result), [&vSmall](std::vector<int>& vb) {
				// Copy only if, none of the "small" combinations is included in the "big" combinations 
				return std::none_of(vSmall.begin(), vSmall.end(), [&vb](std::vector<int>& vs) {
					return std::includes(vb.begin(), vb.end(), vs.begin(), vs.end()); }); });

			// Iterate over all resulting combinations
			for (const std::vector<int>& r : result) {
				
				// out all single values from this combination
				std::copy(r.begin(), r.end(), std::ostream_iterator<int>(ofsResult, " "));
				ofsResult << "\n";
			}
		}
	}
	return 0;
}
