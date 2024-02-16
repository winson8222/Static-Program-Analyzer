#include "sp/SPTokenizer/FileProcessor.h"
#include <fstream>
#include <filesystem>
#include <sstream>

std::string FileProcessor::readFileToString(const std::string& filename) {
	// Create an input file stream to read the file
	assertFileExists(filename);
	std::ifstream inputFile(filename);
	std::stringstream buffer;
	buffer << inputFile.rdbuf();
	inputFile.close();
	return buffer.str();
}

void FileProcessor::assertFileExists(const std::string& filename) {
	// Create an input file stream to read the file
	bool exist = std::filesystem ::exists(filename) && std::filesystem::is_regular_file(filename);
	if (!exist) {
		throw std::runtime_error("Error: File either does not exist, or is corrupted!");
	}
}