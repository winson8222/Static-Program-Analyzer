#pragma once

#include "pkb/stores/relationships/RelationshipStore.h"

using namespace std;

class FollowsStore: public RelationshipStore<int, int> {};
