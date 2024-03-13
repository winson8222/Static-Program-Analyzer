#include "sp/DesignExtractor/Extractor/EntityExtractor/ConstantExtractor.h"

// ai-gen start
// prompt: https://chat.openai.com/share/46f838f3-8c53-484f-8bf6-d22f90191973

ConstantExtractor::ConstantExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<ConstantWriter> constantWriter)
    : IEntityExtractor(root) {
    if (!root->equalType(ASTNodeType::CONSTANT)) {
        throw std::invalid_argument("VariableExtractor: root is not of type VARIABLE");
    }
    this->constantWriter = constantWriter;
}

void ConstantExtractor::extract() {
	// Extract all the constant values
    this->constantWriter->insertConstant(stringToInt(root->getValue()));
}

int ConstantExtractor::stringToInt(const std::string& str) {
    size_t processedChars = 0;
    int num = 0;
    try {
        num = std::stoi(str, &processedChars);
        if (processedChars != str.length()) {
            throw std::invalid_argument("String contains non-integer characters.");
        }
    }
    catch (const std::invalid_argument& e) {
        // Handle case where conversion couldn't be performed
        throw std::runtime_error("String cannot be converted to integer.");
    }
    catch (const std::out_of_range& e) {
        // Handle case where number is out of int range
        throw std::runtime_error("Integer is too large");
    }
    return num;
}

// ai-gen end