#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SPTokenizer/LexicalToken.h"
#include "sp/SPTokenizer/FileProcessor.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>

TEST_CASE("Tokenizer invalid cases", "[readFileToString]") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure procedure {}\n"
                                "call call;\n"
                                "read read;\n"
                                "print print;";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));

    std::string actualContent;
    REQUIRE_NOTHROW(actualContent = FileProcessor::readFileToString(filename));
    auto arr = SPTokenizer::tokenize(actualContent);
    std::filesystem::remove(filename);
}