#include "ParentStore.h"

// Constructor for ParentStore.
ParentStore::ParentStore() {
    // Initializes the parentMap and reverseParentMap.

}

// Checks if s1 is the direct parent of s2.
bool ParentStore::isParent(int s1, int s2) {
    // Use the hasKeyValue method from TemplateMapSet to check for the relationship.
    return parentMap.hasKeyValue(s1, s2);
}

// Checks if s1 is an ancestor of s2 in the AST (Parent*).
bool ParentStore::isAncestor(int s1, int s2) {
    // First, check for direct parent relationship.
    if (isParent(s1, s2)) {
        return true;
    }
    // If not direct, check for any indirect parent relationship.
    for (const auto& child : parentMap.getValuesByKey(s1)) {
        if (isAncestor(child, s2)) {
            return true;
        }
    }
    return false;
}

// Retrieves the direct children of a parent statement.
unordered_set<int> ParentStore::getChildren(int s1) {
    // Directly access the set of children from the TemplateMapSet.
    return parentMap.getValuesByKey(s1);
}

// Retrieves the parent of a given statement.
int ParentStore::getParent(int s2) {
    // Check if the child has a parent and return it. If not, return an indicator (e.g., -1).
    auto it = reverseParentMap.find(s2);
    return it != reverseParentMap.end() ? it->second : -1;
}

// Adds a Parent relationship.
void ParentStore::addParent(int parent, int child) {
    // Add the parent-child relationship to the parentMap.
    parentMap.addKeyValue(parent, child);
    // Add the child-parent relationship to the reverseParentMap.
    reverseParentMap[child] = parent;
}
