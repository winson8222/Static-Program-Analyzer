#pragma once

// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/TSrBejqZDhzJU0nYh4NsepD0
#include "SimpleParser.h"
#include <memory>

class SimpleParserFacade {
private:
    SimpleParser parser;

public:
    SimpleParserFacade(const std::string& filename);
    std::shared_ptr<ASTNode> parse();
};
// ai-gen end