// ai-gen start (gpt, 0, e)
// prompt https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

#include <iostream>
#include <vector>
#include <unordered_set>
#include "pkb/PKBWriter.h"
#include "sp/AST/ASTNode.h" // Assuming you have ASTNode defined in ASTNode.h

class DesignExtractor {
public:
    // Constructor taking in the root node of the AST
    DesignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriter> pkbWriter);

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
    std::unordered_set<std::string> extractVariables();

    void DesignExtractor::recursivelyExtractVariables(const std::shared_ptr<ASTNode>& node, std::vector<ASTNode>& variables);

    std::shared_ptr<ASTNode> root;
    std::shared_ptr<PKBWriter> pkbWriter;
};