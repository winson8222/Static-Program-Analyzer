#include "FollowsTStore.h"

bool FollowsTStore::isFollowsT(int preStmtNum, int postStmtNum) {
    return this->preToPostTMap.hasKeyValue(preStmtNum, postStmtNum);
}

void FollowsTStore::addFollowsT(int preStmtNum, int postStmtNum) {
    this->preToPostTMap.add(preStmtNum, postStmtNum);
    this->postToPreTMap.add(postStmtNum, preStmtNum);
}

unordered_map<int, unordered_set<int>> FollowsTStore::getFollowsT() {
    return this->preToPostTMap.getMapSet();
}