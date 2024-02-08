#pragma

#include "PKB.h"

using namespace std;

class PKBWriter {
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
    explicit PKBWriter(const shared_ptr<PKB>& pkb): pkb(pkb) {
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
     * @brief Inserts a "Constant" entity into the PKB.
     * @param constant
     */
    void insertConstant(int &constant) {
      constantStore->addEntity(constant);
    }

    /**
     * @brief Inserts a "Variable" Entity into the PKB.
     * @param variable
     */
    void insertVariable(string &variable) {
      variableStore->addEntity(variable);
    }
    void insertProcedure(string &procedure) {
      procedureStore->addEntity(procedure);
    }

    void insertStatement(int &stmtNum) {
      statementStore->addEntity(stmtNum);
    }
    void insertIf(int &stmtNum) {
      ifStore->addEntity(stmtNum);
    }
    void insertWhile(int &stmtNum) {
      whileStore->addEntity(stmtNum);
    }
    void insertCall(int &stmtNum) {
      callStore->addEntity(stmtNum);
    }
    void insertAssign(int &stmtNum) {
      assignStore->addEntity(stmtNum);
    }
    void insertRead(int &stmtNum) {
      readStore->addEntity(stmtNum);
    }
    void insertPrint(int &stmtNum) {
      printStore->addEntity(stmtNum);
    }

    // Relationships
    /**
     * @brief Inserts a Follows relationship "Follows(stmt1, stmt2)".
     * @param stmt1
     * @param stmt2
     */
    void insertFollows(int &stmt1, int &stmt2) {
      followsStore->addRelationship(stmt1, stmt2);
    }
    void insertFollowsT(int &stmt1, int &stmt2) {
      followsTStore->addRelationship(stmt1, stmt2);
    }
    void insertParent(int &stmt1, int &stmt2) {
       parentStore->addRelationship(stmt1, stmt2);
    }
    void insertParentT(int &stmt1, int &stmt2) {
      parentTStore->addRelationship(stmt1, stmt2);
    }
    void insertUsesP(string &procedure, string &variable) {
      usesPStore->addRelationship(procedure, variable);
    }
    void insertUsesS(int &stmt, string &variable) {
        throw "Not implemented";
    }
    void insertModifiesP(string &procedure, string &variable) {
        throw "Not implemented";
    }
    void insertModifiesS(int &stmt, string &variable) {
        throw "Not implemented";
    }


};


