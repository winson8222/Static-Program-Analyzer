#include "Tokenizer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>


std::vector<std::string> Tokenizer::splitLine(const std::string& content) {
    std::vector<std::string> result;
    std::istringstream stream(content); // Create a stringstream from the content
    std::string line;

    while (std::getline(stream, line)) {
        result.push_back(line);
    }

    return result;
}


std::vector<Token> Tokenizer::tokenize(std::vector<std::string> inputStream) {
    std::vector<Token> results;
    return results;
}


std::string Tokenizer::readFileToString(const std::string& filename) {
    // Create an input file stream to read the file
    std::ifstream inputFile(filename);

    // Check if the file was opened successfully
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Unable to open the input file.");
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();

    inputFile.close();

    std::cout << buffer.str() << std::endl;

    return buffer.str();
}