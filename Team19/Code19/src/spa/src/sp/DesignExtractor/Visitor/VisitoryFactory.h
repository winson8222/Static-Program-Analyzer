#pragma once

#include <memory>
#include "sp/AST/ASTNode.h"
#include "sp/DesignExtractor/Visitor/IVisitor.h"

#include "sp/DesignExtractor/Visitor/AssignVisitor.h"
#include "sp/DesignExtractor/Visitor/CallVisitor.h"
#include "sp/DesignExtractor/Visitor/IfElseThenVisitor.h"
#include "sp/DesignExtractor/Visitor/PrintVisitor.h"
#include "sp/DesignExtractor/Visitor/ReadVisitor.h"
#include "sp/DesignExtractor/Visitor/WhileVisitor.h"

typedef std::vector<std::shared_ptr<ASTNode>> listnode;

class StatementFactory  {
public:
    std::shared_ptr<StatementVisitor> createVisitor(std::shared_ptr<ASTNode> node, listnode parent, std::shared_ptr<PKBWriterManager> pkbWriterManager);
};

class ExpressionFactory  {
    std::shared_ptr<IVisitor> createVisitor(std::shared_ptr<ASTNode> node, std::shared_ptr<PKBWriterManager> pkbWriterManager);
};