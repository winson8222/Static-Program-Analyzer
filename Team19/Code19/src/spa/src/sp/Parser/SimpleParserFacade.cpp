// ai-gen start(gpt,0,e)
// Prompt: https://platform.openai.com/playground/p/TSrBejqZDhzJU0nYh4NsepD0
#include "SimpleParserFacade.h"

SimpleParserFacade::SimpleParserFacade(const std::string& filename) : parser(filename) {}

std::shared_ptr<ASTNode> SimpleParserFacade::parse() {
    return parser.parseProgram();
}
// ai-gen end