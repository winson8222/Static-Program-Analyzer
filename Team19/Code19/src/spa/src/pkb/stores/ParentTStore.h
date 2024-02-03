#pragma once

#include <unordered_map>
#include <unordered_set>
#include "pkb/templates/TemplateMapSet.h"

using namespace std;

class ParentTStore {
protected:
    // Maps a parent statement to all of its descendant statements
    TemplateMapSet<int, int> ancestorMap;

public:
    ParentTStore();

    // Check if s1 is an ancestor of s2
    virtual bool isAncestor(int s1, int s2) = 0;

    // Add a transitive parent relationship
    virtual void addAncestor(int parent, int descendant) = 0;

    // Get all descendants of a parent statement
    virtual unordered_set<int> getDescendants(int s1) = 0;

    // Clear all transitive relationships
    virtual void clear() = 0;
};
