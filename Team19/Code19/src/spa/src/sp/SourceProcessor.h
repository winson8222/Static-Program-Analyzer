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

	/*
	* @brief Constructor for SourceProcessor, initializes the parser and pkbManager
	*/
	SourceProcessor(std::string filename, std::shared_ptr<PKBManager> pkbManager);

	/*
	* @brief Reset the SourceProcessor to its initial state with no stored cache.
	* This method is set here as prototype for future optimization of SP runtime.
	*/
	void reset();

	/*
	* @brief Parse the SIMPLE source code and build the AST
	* This method takes in the filename, called on the Tokenizer to tokenize the source code
	* into array of LexicalToken, then called on the parser to parse the array of LexicalToken
	* and build the AST from the parsed source code, and save the root of the AST to this.
	*/
	void parseSIMPLE();

	/*
	* @brief Extract the information from the AST and populate the PKB with all necessary information
	* This method uses the DesignExtractor to extract all the information from the AST through visitors
	* and extractors, then push to PKBWriterManager to insert entities and relationships into PKB.
	*/
	void extractAndPopulate();
};