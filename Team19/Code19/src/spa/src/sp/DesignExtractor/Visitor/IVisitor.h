#pragma once

#include <memory>
#include "sp/AST/ASTNode.h" // Assuming you have ASTNode defined in ASTNode.h
#include "pkb/PKBWriterManager.h"

class AssignNode;
class ReadNode;
class PrintNode;
class CallNode;
class WhileNode;
class IfNode;
class VariableNode;
class ConstantNode;
class ProcedureNode;
class StatementListNode;
// Forward declarations for other node types...

// https://chat.openai.com/share/7d5c29d9-43f6-4c36-b04e-0fca3b0e96ff

class IVisitor {
public:
    virtual void visit(AssignNode& node) = 0;
    virtual void visit(ReadNode& node) = 0;
    virtual void visit(PrintNode& node) = 0;
    virtual void visit(CallNode& node) = 0;
    virtual void visit(WhileNode& node) = 0;
    virtual void visit(IfNode& node) = 0;
    virtual void visit(ProcedureNode& node) = 0;
    virtual void visit(StatementListNode& node) = 0;
    // Add more visit methods for other specific node types

    virtual ~IVisitor() {}
    explicit IVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: root(root), pkbWriterManager(pkbWriterManager) {}
    
private:
    std::shared_ptr<ASTNode> root;
    std::shared_ptr<PKBWriterManager> pkbWriterManager;
};
