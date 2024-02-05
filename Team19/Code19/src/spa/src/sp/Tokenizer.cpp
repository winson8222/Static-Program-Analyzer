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
        std::cout << line << std::endl;
        result.push_back(line);
    }

    return result;
}


void Token::print() {
    std::cout << "Line Number: " << lineNumber << " ";
    std::cout << "Line Position: " << linePosition << " ";
    std::cout << "Name: " << name << " ";
    std::cout << "Integer: " << integer << std::endl;

}


std::vector<Token> Tokenizer::tokenize(const std::string& content) {
    std::vector<Token> results;

    int currentLine = 1;
    std::vector<std::string> lines = Tokenizer::splitLine(content);

    for (const std::string& line : lines) {
        std::string originalLine = line;
        while (!line.empty()) {
            bool matchedSomething = false;
            for (const auto& rule : rules) {
                std::smatch match;
                if (std::regex_search(line, match, std::regex(rule.second))) {
                    Token token(rule.first);
                    token.lineNumber = currentLine;
                    token.linePosition = static_cast<int>(originalLine.size() - line.size());
                    if (rule.first == TokenType::NAME) {
                        token.name = match.str();
                    }
                    else if (rule.first == TokenType::INTEGER) {
                        token.integer = match.str();
                    }
                    results.push_back(token);
                    matchedSomething = true;
                    originalLine = originalLine.substr(match.str().size());
                    break;
                }
            }
            if (!matchedSomething) {
                break;
            }
        }
        currentLine++;
    }

    for (auto t : results) {
        t.print();
    }
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

    return buffer.str();
}