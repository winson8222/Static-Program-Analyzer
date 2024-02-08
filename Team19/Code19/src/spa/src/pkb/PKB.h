#pragma once

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

class PKB {
private:
    // Relationship stores
    shared_ptr<FollowsStore> followsStore;
    shared_ptr<FollowsTStore> followsTStore;
    shared_ptr<ParentStore> parentStore;
    shared_ptr<ParentTStore> parentTStore;
    shared_ptr<UsesPStore> usesPStore;
    shared_ptr<UsesSStore> usesSStore;
    shared_ptr<ModifiesPStore> modifiesPStore;
    shared_ptr<ModifiesSStore> modifiesSStore;

    // Entity stores
    shared_ptr<StatementStore> statementStore;
    shared_ptr<ReadStore> readStore;
    shared_ptr<PrintStore> printStore;
    shared_ptr<CallStore> callStore;
    shared_ptr<WhileStore> whileStore;
    shared_ptr<IfStore> ifStore;
    shared_ptr<AssignStore> assignStore;
    shared_ptr<VariableStore> variableStore;
    shared_ptr<ConstantStore> constantStore;
    shared_ptr<ProcedureStore> procedureStore;
public:
    PKB() {
        // Initialise all relationship stores
        followsTStore = make_shared<FollowsTStore>();
        followsStore = make_shared<FollowsStore>();
        parentStore = make_shared<ParentStore>();
        parentTStore = make_shared<ParentTStore>();
        usesPStore = make_shared<UsesPStore>();
        usesSStore = make_shared<UsesSStore>();
        modifiesPStore = make_shared<ModifiesPStore>();
        modifiesSStore = make_shared<ModifiesSStore>();

        // Initialize all entities stores
        statementStore = make_shared<StatementStore>();
        readStore = make_shared<ReadStore>();
        printStore = make_shared<PrintStore>();
        callStore = make_shared<CallStore>();
        whileStore = make_shared<WhileStore>();
        ifStore = make_shared<IfStore>();
        assignStore = make_shared<AssignStore>();
        variableStore = make_shared<VariableStore>();
        constantStore = make_shared<ConstantStore>();
        procedureStore = make_shared<ProcedureStore>();
    }

    // Relationship Getters
    shared_ptr<FollowsStore> getFollowsStore() { return followsStore; }
    shared_ptr<FollowsTStore> getFollowsTStore() { return followsTStore; }
    shared_ptr<ParentStore> getParentStore() { return parentStore; }
    shared_ptr<ParentTStore> getParentTStore() { return parentTStore; }
    shared_ptr<UsesPStore> getUsesPStore() { return usesPStore; }
    shared_ptr<UsesSStore> getUsesSStore() { return usesSStore; }
    shared_ptr<ModifiesPStore> getModifiesPStore() { return modifiesPStore; }
    shared_ptr<ModifiesSStore> getModifiesSStore() { return modifiesSStore; }

    // Entity Getters
    shared_ptr<StatementStore> getStatementStore() { return statementStore; }
    shared_ptr<ReadStore> getReadStore() { return readStore; }
    shared_ptr<PrintStore> getPrintStore() { return printStore; }
    shared_ptr<CallStore> getCallStore() { return callStore; }
    shared_ptr<WhileStore> getWhileStore() { return whileStore; }
    shared_ptr<IfStore> getIfStore() { return ifStore; }
    shared_ptr<AssignStore> getAssignStore() { return assignStore; }
    shared_ptr<VariableStore> getVariableStore() { return variableStore; }
    shared_ptr<ConstantStore> getConstantStore() { return constantStore; }
    shared_ptr<ProcedureStore> getProcedureStore() { return procedureStore; }
};
