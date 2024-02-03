#pragma once

#include "pkb/templates/TemplateMapSet.h"

using namespace std;

class FollowsTStore {
private:
    // The map that stores the Follows* relationship
    TemplateMapSet<int, int> preToPostTMap;
    // The map that stores the reverse Follows* relationship
    TemplateMapSet<int, int> postToPreTMap;
public:
    /**
     * Returns true if the Follows* relationship exists
     * @param preStmtNum
     * @param postStmtNum
     * @return true if the Follows* relationship exists
     */
    bool isFollowsT(int preStmtNum, int postStmtNum);

    /**
     * Adds a Follows* relationship to the map
     * @param preStmtNum
     * @param postStmtNum
     */
    void addFollowsT(int preStmtNum, int postStmtNum);

    /**
     * Gets the Follows* map
     * @return Follows* map (preToPostTMap)
     */
    unordered_map<int, unordered_set<int>> getFollowsT();
};
