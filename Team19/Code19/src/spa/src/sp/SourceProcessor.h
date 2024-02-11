#include "sp/Tokenizer.h"
#include "sp/LexicalToken.h"
#include "sp/Parser/SimpleParser.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"

class SourceProcessor {
public:
	std::vector<LexicalToken> tokens;
	ASTNode* root;
	PKBManager pkbManager;


	SourceProcessor(PKBManager pkbManager);
	void reset();
	void tokenize(std::string filepath);
	void parse();
	void buildAST();
	void extractAndPopulate();
};