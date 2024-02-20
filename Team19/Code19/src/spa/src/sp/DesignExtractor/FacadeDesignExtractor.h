#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

#include "pkb/PKBWriterManager.h"
#include "sp/AST/ASTNode.h"
#include "sp/DesignExtractor/Visitor/IVisitor.h"

#include "sp/DesignExtractor/Visitor/AssignVisitor.h"
#include "sp/DesignExtractor/Visitor/CallVisitor.h"
#include "sp/DesignExtractor/Visitor/IfElseThenVisitor.h"
#include "sp/DesignExtractor/Visitor/PrintVisitor.h"
#include "sp/DesignExtractor/Visitor/ReadVisitor.h"
#include "sp/DesignExtractor/Visitor/WhileVisitor.h"
#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"

#include "sp/DesignExtractor/Extractor/AssignExtractor.h"
#include "sp/DesignExtractor/Extractor/CallExtractor.h"
#include "sp/DesignExtractor/Extractor/IfElseThenExtractor.h"
#include "sp/DesignExtractor/Extractor/PrintExtractor.h"
#include "sp/DesignExtractor/Extractor/ReadExtractor.h"
#include "sp/DesignExtractor/Extractor/WhileExtractor.h"
#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"
#include "sp/DesignExtractor/Extractor/ParentExtractor.h"
#include "sp/DesignExtractor/Extractor/ModifiesExtractor.h"
#include "sp/DesignExtractor/Extractor/ModifiesExtractor.h"
#include "sp/DesignExtractor/Extractor/UsesExtractor.h"
#include "sp/DesignExtractor/Extractor/ConstantExtractor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"

/*
Implementation notes:

*/

class FDesignExtractor {
public:
    FDesignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
        : root(root), pkbWriterManager(pkbWriterManager) {}

    void extractAll();

private:
    std::shared_ptr<ASTNode> root;
    std::shared_ptr<PKBWriterManager> pkbWriterManager;
};