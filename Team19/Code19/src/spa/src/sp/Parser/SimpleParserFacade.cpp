// ai-gen start(gpt,0,e)
// Prompt: https://platform.openai.com/playground/p/TSrBejqZDhzJU0nYh4NsepD0
#include "SimpleParserFacade.h"

SimpleParserFacade::SimpleParserFacade(const std::string& filename) {
	std::string fileContent = FileProcessor::readFileToString(filename);
	std::vector<LexicalToken> tokens = SPTokenizer::tokenize(fileContent);
	auto& token_ptr = std::make_shared<std::vector<LexicalToken>>(tokens);
	parser = std::make_unique<SimpleParser>(token_ptr);
}

std::shared_ptr<ASTNode> SimpleParserFacade::parse() {
	std::shared_ptr<ASTNode> tree_ptr = parser->parseProgram();
	return tree_ptr;
}
// ai-gen end