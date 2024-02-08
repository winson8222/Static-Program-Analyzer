#pragma

#include "PKB.h"

using namespace std;

class PKBReader {
private:
    shared_ptr<PKB> pkb;

    shared_ptr<FollowsStore> followsStore;

    shared_ptr<AssignStore> assignStore;
    shared_ptr<VariableStore> variableStore;

public:
    explicit PKBReader(const shared_ptr<PKB>& pkb): pkb(pkb) {
        followsStore = pkb->getFollowsStore();
        assignStore = pkb->getAssignStore();
        variableStore = pkb->getVariableStore();
    }
    // Entities
    unordered_set<int> getAllAssigns() {
        return assignStore->getAllEntities();
    }

    unordered_set<string> getAllVariables() {
        return variableStore->getAllEntities();
    }

    unordered_set<int> getPreFollows(int stmt) {
        return followsStore->getRelationshipsByValue(stmt);
    }
    unordered_set<int> getPostFollows(int stmt) {
        return followsStore->getRelationshipsByKey(stmt);
    }
};


