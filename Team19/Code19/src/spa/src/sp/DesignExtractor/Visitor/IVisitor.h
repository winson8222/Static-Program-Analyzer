#pragma once

#include <memory>
#include <vector>
#include "sp/AST/ASTNode.h" // Assuming you have ASTNode defined in ASTNode.h
#include "pkb/PKBWriterManager.h"

// ai-gen start

// https://chat.openai.com/share/7d5c29d9-43f6-4c36-b04e-0fca3b0e96ff

typedef std::vector<std::shared_ptr<ASTNode>> listnode;

class IVisitor {
public:
    virtual void visit() = 0;
    // Add more visit methods for other specific node types

    virtual ~IVisitor() {}
    explicit IVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: root(root), pkbWriterManager(pkbWriterManager) {}
    
    std::shared_ptr<ASTNode> root;
    std::shared_ptr<PKBWriterManager> pkbWriterManager;

    std::vector<std::shared_ptr<ASTNode>> contexts;
};

class StatementVisitor : public IVisitor {
public:
    StatementVisitor(std::shared_ptr<ASTNode> root,
        listnode contexts,
        std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {
    	this->contexts = listnode(contexts.begin(), contexts.end());
    }
    virtual void visit() = 0;
    virtual void addContext(std::shared_ptr<ASTNode> context) = 0;
};

// ai-gen end