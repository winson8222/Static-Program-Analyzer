#include "sp/Tokenizer.h"
#include "sp/LexicalToken.h"
#include "pkb/PKBManager.h"

class SourceProcessor {
public:
	// SourceProcessor(PKBManager pkbManager);
	void parseSource(std::string filepath);
	void populatePKB();

private:
	// PKBManager pkbManager;
};