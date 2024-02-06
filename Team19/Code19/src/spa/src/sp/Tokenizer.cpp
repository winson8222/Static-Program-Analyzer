#include "Tokenizer.h"
#include "LexicalToken.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

/*
// prototype for matching rules
extern std::unordered_map<TokenType, std::string> rules = {
        { TokenType::KEYWORD_PROCEDURE, "^(procedure)\\b" },
        { TokenType::NAME, "^([a-zA-Z]\\w*)\\b" },
        { TokenType::INTEGER, "^(\\d+)" },
        { TokenType::OPERATOR_PLUS, "^(\\+)" },
        { TokenType::OPERATOR_EQUAL, "^(=)" },
        { TokenType::SEMICOLON, "^(;)" },
        { TokenType::WHITESPACE, "^(\\s+)" },
        { TokenType::LEFT_BRACKET, "^(\\{)" },
        { TokenType::RIGHT_BRACKET, "^(\\})" }
};

extern std::unordered_map<TokenType, std::string> printer = {
        { TokenType::KEYWORD_PROCEDURE, "procedure"},
        { TokenType::NAME, "name" },
        { TokenType::INTEGER, "integer" },
        { TokenType::OPERATOR_PLUS, "plus" },
        { TokenType::OPERATOR_EQUAL, "equal" },
        { TokenType::SEMICOLON, "semicolon" },
        { TokenType::WHITESPACE, "whitespace" },
        { TokenType::LEFT_BRACKET, "left bracket" },
        { TokenType::RIGHT_BRACKET, "right bracket" }
};
*/

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
    std::cout << "Token Type: " << LexicalTokenMapper::tokenToStringMap.find(type)->second << " ";
    std::cout << "Line Number: " << lineNumber << " ";
    std::cout << "Line Position: " << linePosition << " ";
    std::cout << "Value: " << value << std::endl;

}


std::vector<Token> Tokenizer::tokenize(const std::string& content) {
    std::vector<Token> results;

    
    std::vector<std::string> lines = Tokenizer::splitLine(content);
    int lineNumber = 1;

    for (; lineNumber <= static_cast<int>(lines.size()); lineNumber++) {
        std::string line = lines[lineNumber - 1];
        std::string originalLine = line.substr();
        while (!line.empty()) {
            bool matchedSomething = false;
            for (auto const& rule : LexicalTokenMapper::tokenToRegexMap) {
                std::smatch match;
                if (std::regex_search(line, match, std::regex(rule.second))) {
                    std::cout << match.str() << std::endl;
                    Token t(rule.first);
                    t.lineNumber = lineNumber;
                    t.linePosition = (int)(originalLine.size() - line.size());
                    t.value = match.str();


                    if (t.type != LexicalToken::WHITESPACE) {
                        results.push_back(t);
                    }

                    matchedSomething = true;
                    line = line.substr(match.str().size());
                    break;
                }
            }

            if (!matchedSomething) {
                std::cout << "Error" << std::endl;
            }
        }

        if (lineNumber != lines.size()) {
            Token newLine(LexicalToken::WHITESPACE);
            newLine.lineNumber = lineNumber;
            results.push_back(newLine);
        }
    }

    for (auto it : results) {
        it.print();
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