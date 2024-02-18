#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "pkb/PKBWriterManager.h"
#include "sp/AST/ASTNode.h" // Assuming you have ASTNode defined in ASTNode.h
#include "sp/DesignExtractor/Visitor/IVisitor.h"

class FDesignExtractor {
public:
    FDesignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
        : root(root), pkbWriterManager(pkbWriterManager) {}

    void extractAll() {
        // Example: Extracting variables using VariableExtractorVisitor
       
        // Use the extracted data to populate PKB or perform other actions
    }

private:
    std::shared_ptr<ASTNode> root;
    std::shared_ptr<PKBWriterManager> pkbWriterManager;
};