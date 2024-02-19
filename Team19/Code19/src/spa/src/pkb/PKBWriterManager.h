#pragma once

#include <memory>

#include "PKB.h"

#include "pkb/writers/entities/AssignWriter.h"
#include "pkb/writers/entities/VariableWriter.h"
#include "pkb/writers/entities/ProcedureWriter.h"
#include "pkb/writers/entities/ConstantWriter.h"
#include "pkb/writers/entities/StatementWriter.h"
#include "pkb/writers/entities/IfWriter.h"
#include "pkb/writers/entities/WhileWriter.h"
#include "pkb/writers/entities/CallWriter.h"
#include "pkb/writers/entities/ReadWriter.h"
#include "pkb/writers/entities/PrintWriter.h"

#include "pkb/writers/relationships/FollowsWriter.h"
#include "pkb/writers/relationships/FollowsTWriter.h"
#include "pkb/writers/relationships/ParentWriter.h"
#include "pkb/writers/relationships/ParentTWriter.h"
#include "pkb/writers/relationships/UsesPWriter.h"
#include "pkb/writers/relationships/UsesSWriter.h"
#include "pkb/writers/relationships/ModifiesPWriter.h"
#include "pkb/writers/relationships/ModifiesSWriter.h"

#include "pkb/writers/patterns/AssignPatternWriter.h"

class PKBWriterManager {
private:
    std::shared_ptr<PKB> pkb;

    std::shared_ptr<FollowsWriter> followsWriter;
    std::shared_ptr<FollowsTWriter> followsTWriter;
    std::shared_ptr<ParentWriter> parentWriter;
    std::shared_ptr<ParentTWriter> parentTWriter;
    std::shared_ptr<UsesPWriter> usesPWriter;
    std::shared_ptr<UsesSWriter> usesSWriter;
    std::shared_ptr<ModifiesPWriter> modifiesPWriter;
    std::shared_ptr<ModifiesSWriter> modifiesSWriter;

    std::shared_ptr<AssignWriter> assignWriter;
    std::shared_ptr<VariableWriter> variableWriter;
    std::shared_ptr<ConstantWriter> constantWriter;
    std::shared_ptr<ProcedureWriter> procedureWriter;
    std::shared_ptr<StatementWriter> statementWriter;
    std::shared_ptr<IfWriter> ifWriter;
    std::shared_ptr<WhileWriter> whileWriter;
    std::shared_ptr<CallWriter> callWriter;
    std::shared_ptr<ReadWriter> readWriter;
    std::shared_ptr<PrintWriter> printWriter;

    std::shared_ptr<AssignPatternWriter> assignPatternWriter;

public:
    explicit PKBWriterManager(const std::shared_ptr<PKB>& pkb): pkb(pkb) {
      followsWriter = std::make_shared<FollowsWriter>(pkb->getFollowsStore());
      followsTWriter = std::make_shared<FollowsTWriter>(pkb->getFollowsTStore());
      parentWriter = std::make_shared<ParentWriter>(pkb->getParentStore());
      parentTWriter = std::make_shared<ParentTWriter>(pkb->getParentTStore());
      usesPWriter = std::make_shared<UsesPWriter>(pkb->getUsesPStore());
      usesSWriter = std::make_shared<UsesSWriter>(pkb->getUsesSStore());
      modifiesPWriter = std::make_shared<ModifiesPWriter>(pkb->getModifiesPStore());
      modifiesSWriter = std::make_shared<ModifiesSWriter>(pkb->getModifiesSStore());

      assignWriter = std::make_shared<AssignWriter>(pkb->getAssignStore());
      variableWriter = std::make_shared<VariableWriter>(pkb->getVariableStore());
      constantWriter = std::make_shared<ConstantWriter>(pkb->getConstantStore());
      procedureWriter = std::make_shared<ProcedureWriter>(pkb->getProcedureStore());
      statementWriter = std::make_shared<StatementWriter>(pkb->getStatementStore());
      ifWriter = std::make_shared<IfWriter>(pkb->getIfStore());
      whileWriter = std::make_shared<WhileWriter>(pkb->getWhileStore());
      callWriter = std::make_shared<CallWriter>(pkb->getCallStore());
      readWriter = std::make_shared<ReadWriter>(pkb->getReadStore());
      printWriter = std::make_shared<PrintWriter>(pkb->getPrintStore());

      assignPatternWriter = std::make_shared<AssignPatternWriter>(pkb->getAssignPatternStore());
    }
    // Relationships
    std::shared_ptr<FollowsWriter> getFollowsWriter() {
      return followsWriter;
    }

    std::shared_ptr<FollowsTWriter> getFollowsTWriter() {
      return followsTWriter;
    }

    std::shared_ptr<ParentWriter> getParentWriter() {
      return parentWriter;
    }

    std::shared_ptr<ParentTWriter> getParentTWriter() {
      return parentTWriter;
    }

    std::shared_ptr<UsesPWriter> getUsesPWriter() {
      return usesPWriter;
    }

    std::shared_ptr<UsesSWriter> getUsesSWriter() {
      return usesSWriter;
    }

    std::shared_ptr<ModifiesPWriter> getModifiesPWriter() {
      return modifiesPWriter;
    }

    std::shared_ptr<ModifiesSWriter> getModifiesSWriter() {
      return modifiesSWriter;
    }

    // Entities
    std::shared_ptr<VariableWriter> getVariableWriter() {
      return variableWriter;
    }

    std::shared_ptr<ConstantWriter> getConstantWriter() {
      return constantWriter;
    }

    std::shared_ptr<ProcedureWriter> getProcedureWriter() {
      return procedureWriter;
    }

    std::shared_ptr<StatementWriter> getStatementWriter() {
      return statementWriter;
    }

    std::shared_ptr<IfWriter> getIfWriter() {
      return ifWriter;
    }

    std::shared_ptr<WhileWriter> getWhileWriter() {
      return whileWriter;
    }

    std::shared_ptr<CallWriter> getCallWriter() {
      return callWriter;
    }

    std::shared_ptr<ReadWriter> getReadWriter() {
      return readWriter;
    }

    std::shared_ptr<PrintWriter> getPrintWriter() {
      return printWriter;
    }

    std::shared_ptr<AssignWriter> getAssignWriter() {
      return assignWriter;
    }

    // Patterns
    std::shared_ptr<AssignPatternWriter> getAssignPatternWriter() {
      return assignPatternWriter;
    }

};


