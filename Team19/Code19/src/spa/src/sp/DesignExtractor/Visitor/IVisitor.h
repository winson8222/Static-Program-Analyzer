#pragma once

#include <memory>
#include <vector>
#include "sp/AST/ASTNode.h" 
#include "sp/AST/ASTUtility.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ParentExtractor.h"
#include "pkb/PKBWriterManager.h"

// ai-gen start(chatgpt, 2, e)
// prompt: https://chat.openai.com/share/7d5c29d9-43f6-4c36-b04e-0fca3b0e96ff

/*
* Shortened definition of a list of ASTNode pointers for convenience
* Note: This should only be used inside DesignExtractor/Visitor classes
*/
typedef std::vector<std::shared_ptr<ASTNode>> listnode;

/*
* Abstract class for the Visitor pattern, which all other visitors will inherit from
*/
class IVisitor {
public:
    /*
    * The destructor for the IVisitor class
    */
    virtual ~IVisitor() {}

    /*
    * The constructor for the IVisitor class in default
    */
    explicit IVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
        : root(root), pkbWriterManager(pkbWriterManager) {}

    /*
    * The visit method that will be implemented by all visitors,
    * which recursively visits the AST and performs the necessary operations
    * in depth-first-search manner
    */
    virtual void visit() = 0;
    
    // all these methods should be set to private at some point
    std::shared_ptr<ASTNode> root;
    std::shared_ptr<PKBWriterManager> pkbWriterManager;
    std::vector<std::shared_ptr<ASTNode>> contexts;
};

/*
* Additional abstract class which group all Statements under a pattern
* It is used to group statements like assignment, while, if, call, and print, read.
*/
class StatementVisitor : public IVisitor {
public:
    /*
    * The constructor for the StatementVisitor class, which takes in the root node of the AST,
    * a list of contexts (previous relevant nodes), and a PKBWriterManager.
    */
    StatementVisitor(std::shared_ptr<ASTNode> root, listnode contexts,
        std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {
    	this->contexts = listnode(contexts.begin(), contexts.end());
    }
    
    /*
    * The visit method that will be implemented by all StatementVisitors,
    * as inherited from the IVisitor class
    */
    virtual void visit() = 0;

    /*
    * The method to set the parents of the contexts, which takes in
    * a list of context, the current nodes, and a PKBWriterManager,
    * commonly then recursively traverses the AST to set the parents of the contexts if
    * the node is not a procedure node
	*/
    void setParents(listnode contexts, std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);
};

// ai-gen end
