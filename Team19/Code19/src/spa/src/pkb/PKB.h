#pragma once

#include <memory>

#include "pkb/stores/relationships/types/FollowsStore.h"
#include "pkb/stores/relationships/types/FollowsTStore.h"
#include "pkb/stores/relationships/types/UsesPStore.h"
#include "pkb/stores/relationships/types/UsesSStore.h"
#include "pkb/stores/relationships/types/ParentStore.h"
#include "pkb/stores/relationships/types/ParentTStore.h"
#include "pkb/stores/relationships/types/ModifiesPStore.h"
#include "pkb/stores/relationships/types/ModifiesSStore.h"
#include "pkb/stores/entities/types/StatementStore.h"
#include "pkb/stores/entities/types/ReadStore.h"
#include "pkb/stores/entities/types/PrintStore.h"
#include "pkb/stores/entities/types/CallStore.h"
#include "pkb/stores/entities/types/WhileStore.h"
#include "pkb/stores/entities/types/IfStore.h"
#include "pkb/stores/entities/types/AssignStore.h"
#include "pkb/stores/entities/types/VariableStore.h"
#include "pkb/stores/entities/types/ConstantStore.h"
#include "pkb/stores/entities/types/ProcedureStore.h"
#include "pkb/stores/patterns/assign/AssignPatternStore.h"
#include "pkb/stores/patterns/control/IfPatternStore.h"
#include "pkb/stores/patterns/control/WhilePatternStore.h"
#include <memory>

class PKB {
private:
    // Relationship stores
    std::shared_ptr<FollowsStore> followsStore;
    std::shared_ptr<FollowsTStore> followsTStore;
    std::shared_ptr<ParentStore> parentStore;
    std::shared_ptr<ParentTStore> parentTStore;
    std::shared_ptr<UsesPStore> usesPStore;
    std::shared_ptr<UsesSStore> usesSStore;
    std::shared_ptr<ModifiesPStore> modifiesPStore;
    std::shared_ptr<ModifiesSStore> modifiesSStore;

    // Entity stores
    std::shared_ptr<StatementStore> statementStore;
    std::shared_ptr<ReadStore> readStore;
    std::shared_ptr<PrintStore> printStore;
    std::shared_ptr<CallStore> callStore;
    std::shared_ptr<WhileStore> whileStore;
    std::shared_ptr<IfStore> ifStore;
    std::shared_ptr<AssignStore> assignStore;
    std::shared_ptr<VariableStore> variableStore;
    std::shared_ptr<ConstantStore> constantStore;
    std::shared_ptr<ProcedureStore> procedureStore;

    // Pattern stores
    std::shared_ptr<AssignPatternStore> assignPatternStore;
    std::shared_ptr<IfPatternStore> ifPatternStore;
    std::shared_ptr<WhilePatternStore> whilePatternStore;
public:
    PKB() {
        // Initialise all relationship stores
        followsTStore = std::make_shared<FollowsTStore>();
        followsStore = std::make_shared<FollowsStore>();
        parentStore = std::make_shared<ParentStore>();
        parentTStore = std::make_shared<ParentTStore>();
        usesPStore = std::make_shared<UsesPStore>();
        usesSStore = std::make_shared<UsesSStore>();
        modifiesPStore = std::make_shared<ModifiesPStore>();
        modifiesSStore = std::make_shared<ModifiesSStore>();

        // Initialize all entities stores
        statementStore = std::make_shared<StatementStore>();
        readStore = std::make_shared<ReadStore>();
        printStore = std::make_shared<PrintStore>();
        callStore = std::make_shared<CallStore>();
        whileStore = std::make_shared<WhileStore>();
        ifStore = std::make_shared<IfStore>();
        assignStore = std::make_shared<AssignStore>();
        variableStore = std::make_shared<VariableStore>();
        constantStore = std::make_shared<ConstantStore>();
        procedureStore = std::make_shared<ProcedureStore>();

        // Initialize all pattern stores
        assignPatternStore = std::make_shared<AssignPatternStore>();
        ifPatternStore = std::make_shared<IfPatternStore>();
        whilePatternStore = std::make_shared<WhilePatternStore>();
    }

    // Relationship Getters
    std::shared_ptr<FollowsStore> getFollowsStore() { return followsStore; }
    std::shared_ptr<FollowsTStore> getFollowsTStore() { return followsTStore; }
    std::shared_ptr<ParentStore> getParentStore() { return parentStore; }
    std::shared_ptr<ParentTStore> getParentTStore() { return parentTStore; }
    std::shared_ptr<UsesPStore> getUsesPStore() { return usesPStore; }
    std::shared_ptr<UsesSStore> getUsesSStore() { return usesSStore; }
    std::shared_ptr<ModifiesPStore> getModifiesPStore() { return modifiesPStore; }
    std::shared_ptr<ModifiesSStore> getModifiesSStore() { return modifiesSStore; }

    // Entity Getters
    std::shared_ptr<StatementStore> getStatementStore() { return statementStore; }
    std::shared_ptr<ReadStore> getReadStore() { return readStore; }
    std::shared_ptr<PrintStore> getPrintStore() { return printStore; }
    std::shared_ptr<CallStore> getCallStore() { return callStore; }
    std::shared_ptr<WhileStore> getWhileStore() { return whileStore; }
    std::shared_ptr<IfStore> getIfStore() { return ifStore; }
    std::shared_ptr<AssignStore> getAssignStore() { return assignStore; }
    std::shared_ptr<VariableStore> getVariableStore() { return variableStore; }
    std::shared_ptr<ConstantStore> getConstantStore() { return constantStore; }
    std::shared_ptr<ProcedureStore> getProcedureStore() { return procedureStore; }

    // Pattern Getters
    std::shared_ptr<AssignPatternStore> getAssignPatternStore() { return assignPatternStore; }
    std::shared_ptr<IfPatternStore> getIfPatternStore() { return ifPatternStore; }
    std::shared_ptr<WhilePatternStore> getWhilePatternStore() { return whilePatternStore; }
};
