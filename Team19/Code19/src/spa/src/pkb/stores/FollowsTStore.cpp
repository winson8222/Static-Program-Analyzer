#include "FollowsTStore.h"

bool FollowsTStore::isFollowsT(int preStmtNum, int postStmtNum) {
    return this->preToPostTMap.hasKeyValue(preStmtNum, postStmtNum);
}

void FollowsTStore::addFollowsT(int preStmtNum, int postStmtNum) {
    this->preToPostTMap.addKeyValue(preStmtNum, postStmtNum);
    this->postToPreTMap.addKeyValue(postStmtNum, preStmtNum);
}

unordered_map<int, unordered_set<int>> FollowsTStore::getFollowsT() {
    return this->preToPostTMap.getMapSet();
}

unordered_set<int> FollowsTStore::getPreFollowsT(int postStmtNum) {
    return this->postToPreTMap.getValuesByKey(postStmtNum);
}

unordered_set<int> FollowsTStore::getPostFollowsT(int preStmtNum) {
    return this->preToPostTMap.getValuesByKey(preStmtNum);
}
