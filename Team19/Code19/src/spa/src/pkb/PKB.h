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
#include "pkb/stores/relationships/types/CallsStore.h"
#include "pkb/stores/relationships/types/CallsTStore.h"
#include "pkb/stores/relationships/types/NextStore.h"
#include "pkb/stores/relationships/types/NextTStore.h"
#include "pkb/stores/relationships/types/AffectsStore.h"

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

#include "pkb/stores/links/types/CallProcNameStore.h"
#include "pkb/stores/links/types/ReadVarNameStore.h"
#include "pkb/stores/links/types/PrintVarNameStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
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
    std::shared_ptr<CallsStore> callsStore;
    std::shared_ptr<CallsTStore> callsTStore;
    std::shared_ptr<NextStore> nextStore;
    std::shared_ptr<NextTStore> nextTStore;
	std::shared_ptr<AffectsStore> affectsStore;

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

    // Link stores
    std::shared_ptr<CallProcNameStore> callProcNameStore;
    std::shared_ptr<ReadVarNameStore> readVarNameStore;
    std::shared_ptr<PrintVarNameStore> printVarNameStore;
public:
    PKB() {
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

        // Initialise all relationship stores
        followsTStore = std::make_shared<FollowsTStore>();
        followsStore = std::make_shared<FollowsStore>();
        parentStore = std::make_shared<ParentStore>();
        parentTStore = std::make_shared<ParentTStore>();
        usesPStore = std::make_shared<UsesPStore>();
        usesSStore = std::make_shared<UsesSStore>();
        modifiesPStore = std::make_shared<ModifiesPStore>();
        modifiesSStore = std::make_shared<ModifiesSStore>();
        callsStore = std::make_shared<CallsStore>();
        callsTStore = std::make_shared<CallsTStore>();
        nextStore = std::make_shared<NextStore>();
        nextTStore = std::make_shared<NextTStore>(nextStore, whileStore);
        affectsStore = std::make_shared<AffectsStore>(assignStore, nextStore, usesSStore, modifiesSStore, whileStore, ifStore);

        // Initialize all pattern stores
        assignPatternStore = std::make_shared<AssignPatternStore>();
        ifPatternStore = std::make_shared<IfPatternStore>();
        whilePatternStore = std::make_shared<WhilePatternStore>();

        // Initialize all link stores
        callProcNameStore = std::make_shared<CallProcNameStore>();
        readVarNameStore = std::make_shared<ReadVarNameStore>();
        printVarNameStore = std::make_shared<PrintVarNameStore>();
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
    std::shared_ptr<CallsStore> getCallsStore() { return callsStore; }
    std::shared_ptr<CallsTStore> getCallsTStore() { return callsTStore; }
    std::shared_ptr<NextStore> getNextStore() { return nextStore; }
    std::shared_ptr<NextTStore> getNextTStore() { return nextTStore; }
    std::shared_ptr<AffectsStore> getAffectsStore() { return affectsStore; }

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

    // Link Getters
    std::shared_ptr<CallProcNameStore> getCallProcNameStore() { return callProcNameStore; }
    std::shared_ptr<ReadVarNameStore> getReadVarNameStore() { return readVarNameStore; }
    std::shared_ptr<PrintVarNameStore> getPrintVarNameStore() { return printVarNameStore; }
};
// ai-gen end
