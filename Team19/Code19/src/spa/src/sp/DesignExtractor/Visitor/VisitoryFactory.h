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

/*
* Class to create the visitor for the statement, by using the factory pattern
* to default switching to statement type
*/
class StatementFactory  {
public:
    /*
    * @brief create the visitor for the statement, by using the factory pattern
    * @param node the ASTNode to be visited
    * @param parent the list of ASTNode to be visited
    * @param pkbWriterManager the pkbWriterManager to be visited
    * @return the visitor for the statement
    */
    std::shared_ptr<StatementVisitor> createVisitor(std::shared_ptr<ASTNode> node, 
        listnode parent, 
        std::shared_ptr<PKBWriterManager> pkbWriterManager);
};