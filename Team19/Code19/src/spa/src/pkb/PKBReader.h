#pragma

#include "PKB.h"

using namespace std;

class PKBReader {
private:
    shared_ptr<PKB> pkb;

    shared_ptr<FollowsStore> followsStore;
    shared_ptr<FollowsTStore> followsTStore;

    shared_ptr<ParentStore> parentStore;
    shared_ptr<ParentTStore> parentTStore;

    shared_ptr<UsesPStore> usesPStore;
    shared_ptr<UsesSStore> usesSStore;

    shared_ptr<ModifiesPStore> modifiesPStore;
    shared_ptr<ModifiesSStore> modifiesSStore;

    shared_ptr<AssignStore> assignStore;
    shared_ptr<VariableStore> variableStore;
    shared_ptr<ConstantStore> constantStore;
    shared_ptr<ProcedureStore> procedureStore;
    shared_ptr<StatementStore> statementStore;
    shared_ptr<IfStore> ifStore;
    shared_ptr<WhileStore> whileStore;
    shared_ptr<CallStore> callStore;
    shared_ptr<ReadStore> readStore;
    shared_ptr<PrintStore> printStore;

public:
    explicit PKBReader(const shared_ptr<PKB>& pkb): pkb(pkb) {
        followsStore = pkb->getFollowsStore();
        followsTStore = pkb->getFollowsTStore();

        parentStore = pkb->getParentStore();
        parentTStore = pkb->getParentTStore();

        usesPStore = pkb->getUsesPStore();
        usesSStore = pkb->getUsesSStore();

        modifiesPStore = pkb->getModifiesPStore();
        modifiesSStore = pkb->getModifiesSStore();

        assignStore = pkb->getAssignStore();
        variableStore = pkb->getVariableStore();
        constantStore = pkb->getConstantStore();
        procedureStore = pkb->getProcedureStore();
        statementStore = pkb->getStatementStore();
        ifStore = pkb->getIfStore();
        whileStore = pkb->getWhileStore();
        callStore = pkb->getCallStore();
        readStore = pkb->getReadStore();
        printStore = pkb->getPrintStore();
    }
    // Entities

    /**
     * @brief Gets the statement number of all "Assign" entities.
     * @return unordered_set<int>: Statement number of all "Assign" entities.
     */
    unordered_set<int> getAllAssigns() {
        return assignStore->getAllEntities();
    }

    /**
     * @brief Gets the statement number of all "Variable" entities.
     * @return unordered_set<int>: Statement number of all "Variable" entities.
     */
    unordered_set<string> getAllVariables() {
        return variableStore->getAllEntities();
    }

    // Relationships

    /**
     * @brief Gets the statement number of reversed "Follows" relationships of the given statement.
     * @param stmt: stmt in Follows(s1, stmt)
     * @return unordered_set<int>: Statement number of all s1 in Follows(s1, stmt)
     */
    unordered_set<int> getPreFollows(int stmt) {
        return followsStore->getRelationshipsByValue(stmt);
    }

    /**
     * @brief Gets the statement number of "Follows" relationships of the given statement.
     * @param stmt: stmt in Follows(stmt, s2)
     * @return unordered_set<int>: Statement number of all s2 in Follows(stmt, s2)
     */
    unordered_set<int> getPostFollows(int stmt) {
        return followsStore->getRelationshipsByKey(stmt);
    }


};


