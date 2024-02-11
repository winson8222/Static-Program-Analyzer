#include "sp/Tokenizer.h"
#include "sp/LexicalToken.h"
#include "pkb/PKBManager.h"

class SourceProcessor {
public:
	PKBManager pkbManager;
	SourceProcessor(PKBManager pkbManager);
	void parseSource(std::string filepath);
	void populatePKB();
};