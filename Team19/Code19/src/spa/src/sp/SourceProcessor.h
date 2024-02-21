#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SPTokenizer/LexicalToken.h"
#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/Parser/SimpleParserFacade.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"

/*
* @brief The SourceProcessor class is the facade class that connects
* components of SP together, and connect them to PKB.
* 
* High level abstraction: Initialize and process with SIMPLE parser, AST root node, and PKB
* SIMPLE parser, in turn uses SPTokenizer to tokenize the source code, and build AST then save root
* when extractAndPopulate is called, it uses DesignExtractor to extract information to PKB
* 
* @field parser: the SimpleParserFacade object that will be used to parse the SIMPLE source code
* @field root: the root of the AST that will be built from the parsed source code
* @field pkbManager: the PKBManager object that will be used to store the extracted information
*/

class SourceProcessor {
public:
	SimpleParserFacade parser;
	std::shared_ptr<ASTNode> root;
	std::shared_ptr<PKBManager> pkbManager;

	SourceProcessor(std::string filename, std::shared_ptr<PKBManager> pkbManager);
	void reset();

	void parseSIMPLE();
	void buildAST();

	void extractAndPopulate();
};