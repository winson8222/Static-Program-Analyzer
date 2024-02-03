#pragma once

#include <unordered_set>
#include "pkb/templates/TemplateMapSet.h"
#include "pkb/stores/FollowsTStore.h"

using namespace std;

class FollowsStore: public FollowsTStore {
private:
    /**
     * The map that stores the follows relationship
     * Key: stmt number
     * Value: stmt number
     */
    TemplateMapSet<int, int> followsMap;

    /**
     * The map that stores the reverse follows relationship
     * Key: stmt number
     * Value: stmt number
     */
    TemplateMapSet<int, int> reverseFollowsMap;
public:
    FollowsStore();

    bool isFollows(int preStmtNum, int postStmtNum);
    unordered_set<int> getFollows(int stmtNum);

    void addFollows(int stmt1, int stmt2);



};
