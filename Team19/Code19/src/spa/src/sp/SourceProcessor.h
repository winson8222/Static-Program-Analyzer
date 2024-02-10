#include "sp/Tokenizer.h"
#include "sp/LexicalToken.h"
#include "pkb/PKBManager.h"
#include "pkb/PKB.h"
#include "pkb/PKBReader.h"
#include "pkb/PKBWriter.h"

class SourceProcessor {
public:
	void parseSource(std::string filepath);
	void populatePKB();

private:
	PKB pkb;
	PKBManager pkbManager;
	PKBReader pkbReader;
	PKBWriter pkbWriter;
};