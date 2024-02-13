#include "sp/SPTokenizer/Tokenizer.h"
#include "sp/SPTokenizer/LexicalToken.h"
#include "sp/DesignExtractor/DesignExtractor.h"
#include "sp/Parser/SimpleParser.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"

class SourceProcessor {
public:
	SimpleParser parser;
	std::shared_ptr<ASTNode> root;
	std::shared_ptr<PKBManager> pkbManager;

	SourceProcessor(std::string filename, std::shared_ptr<PKBManager> pkbManager);
	void reset();

	void parseSIMPLE();
	void buildAST();

	void sampleAST();	// for testing purposes
	void extractAndPopulate();
};