#include "sp/SPTokenizer/FileProcessor.h"
#include <fstream>
#include <sstream>

std::string FileProcessor::readFileToString(const std::string& filename) {
	// Create an input file stream to read the file
	std::ifstream inputFile(filename);

	// Check if the file was opened successfully
	if (!inputFile.is_open()) {
		throw std::runtime_error("Error: Unable to open the input file.");
	}

	std::stringstream buffer;
	buffer << inputFile.rdbuf();

	inputFile.close();

	return buffer.str();
}
