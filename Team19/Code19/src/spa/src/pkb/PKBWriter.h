#pragma

#include "PKB.h"

using namespace std;

class PKBWriter {
private:
    shared_ptr<PKB> pkb;

    shared_ptr<FollowsStore> followsStore;

    shared_ptr<AssignStore> assignStore;
    shared_ptr<VariableStore> variableStore;


public:
    explicit PKBWriter(const shared_ptr<PKB>& pkb): pkb(pkb) {
        followsStore = pkb->getFollowsStore();

        assignStore = pkb->getAssignStore();
        variableStore = pkb->getVariableStore();
    }
    // Entities
    void insertConstant(int constant);
    void insertVariable(string variable) {
        variableStore->addEntity(variable);
    }
    void insertProcedure(string procedure);
    void insertStatement(int stmtNum);
    void insertIf(int stmtNum);
    void insertWhile(int stmtNum);
    void insertCall(int stmtNum);
    void insertAssign(int stmtNum) {
        assignStore->addEntity(stmtNum);
    }
    void insertRead(int stmtNum) {
        throw "Not implemented";
    }
    void insertPrint(int stmtNum) {
        throw "Not implemented";
    }

    // Relationships
    void insertFollows(int stmt1, int stmt2) {
        followsStore->addRelationship(stmt1, stmt2);
    }
    void insertFollowsT(int stmt1, int stmt2) {
        throw "Not implemented";
    }
    void insertParent(int stmt1, int stmt2) {
        throw "Not implemented";
    }
    void insertParentT(int stmt1, int stmt2) {
        throw "Not implemented";
    }
    void insertUsesP(int stmt, string variable) {
        throw "Not implemented";
    }
    void insertUsesS(int stmt, string variable) {
        throw "Not implemented";
    }
    void insertModifiesP(int stmt, string variable) {
        throw "Not implemented";
    }
    void insertModifiesS(int stmt, string variable) {
        throw "Not implemented";
    }


};


