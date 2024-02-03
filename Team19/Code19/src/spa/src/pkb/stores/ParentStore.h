//
// Created by Shurvir Arora on 3/2/24.
//

#pragma once

#include <unordered_map>
#include <unordered_set>
#include "pkb/templates/TemplateMapSet.h"
#include "pkb/stores/ParentTStore.h"

using namespace std;

class ParentStore: public ParentTStore {
private:
    /**
     * The map that stores the direct parent relationship (Parent)
     * Key: Parent statement number
     * Value: Set of directly nested child statement numbers
     */
    TemplateMapSet<int, int> parentMap;

    /**
     * The map that stores the reverse parent relationship (children to parents)
     * Key: Child statement number
     * Value: Parent statement number
     */
    unordered_map<int, int> reverseParentMap;

public:
    ParentStore();

    // Check if s1 is the direct parent of s2
    bool isParent(int s1, int s2);
    // Check if s1 is an ancestor of s2 in the AST (Parent*)
    bool isAncestor(int s1, int s2);
    // Get the direct children of a parent statement
    unordered_set<int> getChildren(int s1);
    // Get the parent of a given statement
    int getParent(int s2);
    // Add a Parent relationship
    void addParent(int parent, int child);
};

