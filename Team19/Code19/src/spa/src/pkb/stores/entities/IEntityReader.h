#pragma once

#include <unordered_set>

using namespace std;

template <typename EntityType>
class IEntityReader {
public:
    virtual unordered_set<EntityType> getEntity() = 0;
};