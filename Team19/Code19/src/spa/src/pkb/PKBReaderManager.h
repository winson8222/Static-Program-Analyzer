#pragma once

#include <memory>

#include "PKB.h"

#include "pkb/readers/entities/AssignReader.h"
#include "pkb/readers/entities/VariableReader.h"
#include "pkb/readers/entities/ProcedureReader.h"
#include "pkb/readers/entities/StatementReader.h"
#include "pkb/readers/entities/IfReader.h"
#include "pkb/readers/entities/WhileReader.h"
#include "pkb/readers/entities/CallReader.h"
#include "pkb/readers/entities/ConstantReader.h"
#include "pkb/readers/entities/ReadReader.h"
#include "pkb/readers/entities/PrintReader.h"

#include "pkb/readers/relationships/FollowsReader.h"
#include "pkb/readers/relationships/FollowsTReader.h"
#include "pkb/readers/relationships/ParentReader.h"
#include "pkb/readers/relationships/ParentTReader.h"

#include "pkb/readers/patterns/AssignPatternReader.h"

class PKBReaderManager {
private:
    std::shared_ptr<PKB> pkb;

    std::shared_ptr<AssignReader> assignReader;
    std::shared_ptr<VariableReader> variableReader;
    std::shared_ptr<ProcedureReader> procedureReader;
    std::shared_ptr<StatementReader> statementReader;
    std::shared_ptr<IfReader> ifReader;
    std::shared_ptr<WhileReader> whileReader;
    std::shared_ptr<CallReader> callReader;
    std::shared_ptr<ReadReader> readReader;
    std::shared_ptr<ConstantReader> constantReader;
    std::shared_ptr<PrintReader> printReader;

    std::shared_ptr<FollowsReader> followsReader;
    std::shared_ptr<FollowsTReader> followsTReader;
    std::shared_ptr<ParentReader> parentReader;
    std::shared_ptr<ParentTReader> parentTReader;

    std::shared_ptr<AssignPatternReader> assignPatternReader;

public:
    explicit PKBReaderManager(const std::shared_ptr<PKB>& pkb): pkb(pkb) {
      assignReader = std::make_shared<AssignReader>(pkb->getAssignStore());
      variableReader = std::make_shared<VariableReader>(pkb->getVariableStore());
      procedureReader = std::make_shared<ProcedureReader>(pkb->getProcedureStore());
      statementReader = std::make_shared<StatementReader>(pkb->getStatementStore());
      ifReader = std::make_shared<IfReader>(pkb->getIfStore());
      whileReader = std::make_shared<WhileReader>(pkb->getWhileStore());
      callReader = std::make_shared<CallReader>(pkb->getCallStore());
      readReader = std::make_shared<ReadReader>(pkb->getReadStore());
      constantReader = std::make_shared<ConstantReader>(pkb->getConstantStore());
      printReader = std::make_shared<PrintReader>(pkb->getPrintStore());

      followsReader = std::make_shared<FollowsReader>(pkb->getFollowsStore());
      followsTReader = std::make_shared<FollowsTReader>(pkb->getFollowsTStore());
      parentReader = std::make_shared<ParentReader>(pkb->getParentStore());
      parentTReader = std::make_shared<ParentTReader>(pkb->getParentTStore());

      assignPatternReader = std::make_shared<AssignPatternReader>(pkb->getAssignPatternStore());
    }

    // Entity Readers
    std::shared_ptr<AssignReader> getAssignReader() {
        return assignReader;
    }

    std::shared_ptr<VariableReader> getVariableReader() {
        return variableReader;
    }

    std::shared_ptr<ProcedureReader> getProcedureReader() {
        return procedureReader;
    }

    std::shared_ptr<StatementReader> getStatementReader() {
        return statementReader;
    }

    std::shared_ptr<IfReader> getIfReader() {
        return ifReader;
    }

    std::shared_ptr<WhileReader> getWhileReader() {
        return whileReader;
    }

    std::shared_ptr<CallReader> getCallReader() {
        return callReader;
    }

    std::shared_ptr<ReadReader> getReadReader() {
        return readReader;
    }

    std::shared_ptr<ConstantReader> getConstantReader() {
        return constantReader;
    }

    std::shared_ptr<PrintReader> getPrintReader() {
        return printReader;
    }

    // Relationship Readers

    std::shared_ptr<FollowsReader> getFollowsReader() {
        return followsReader;
    }

    std::shared_ptr<FollowsTReader> getFollowsTReader() {
        return followsTReader;
    }

    std::shared_ptr<ParentReader> getParentReader() {
        return parentReader;
    }

    std::shared_ptr<ParentTReader> getParentTReader() {
        return parentTReader;
    }

    // Pattern Readers
    std::shared_ptr<AssignPatternReader> getAssignPatternReader() {
        return assignPatternReader;
    }
};


