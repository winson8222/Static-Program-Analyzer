// ai-gen start (gpt, 0, e)
// prompt https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

#include <iostream>
#include <vector>
#include <unordered_set>
#include "pkb/PKBWriter.h"
#include "sp/AST/ASTNode.h" // Assuming you have ASTNode defined in ASTNode.h

/*
std::shared_ptr<FollowsStore> followsStore;
std::shared_ptr<FollowsTStore> followsTStore;

std::shared_ptr<ParentStore> parentStore;
std::shared_ptr<ParentTStore> parentTStore;

std::shared_ptr<UsesPStore> usesPStore;
std::shared_ptr<UsesSStore> usesSStore;

std::shared_ptr<ModifiesPStore> modifiesPStore;
std::shared_ptr<ModifiesSStore> modifiesSStore;

std::shared_ptr<AssignStore> assignStore;
std::shared_ptr<VariableStore> variableStore;
std::shared_ptr<ConstantStore> constantStore;
std::shared_ptr<ProcedureStore> procedureStore;
std::shared_ptr<StatementStore> statementStore;
std::shared_ptr<IfStore> ifStore;
std::shared_ptr<WhileStore> whileStore;
std::shared_ptr<CallStore> callStore;
std::shared_ptr<ReadStore> readStore;
std::shared_ptr<PrintStore> printStore;
*/

class DesignExtractor {
public:
    // Constructor taking in the root node of the AST
    DesignExtractor(std::shared_ptr<ASTNode> root);

    const ASTNode& getRoot() const {
        return *root;
    }
    // Method to extract all variables from the AST
    void extractFollows();
    void extractFollowsStar();
    void extractParents();
    void extractParentsStar();
    void extractUses();
    void extractModifies();
    void extractAssigns();
    void extractConstants();
    void extractProcedures();
    void extractStatements();
    void extractIf();
    void extractWhiles();
    void extractCall();
    void extractRead();
    void extractPrint();

    // Recursive function to traverse the AST and extract variables
    void extractVariablesRecursive(ASTNode* node, std::unordered_set<std::string>& variables);

    std::shared_ptr<ASTNode> root;
};