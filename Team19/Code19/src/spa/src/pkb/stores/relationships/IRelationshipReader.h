#pragma once

#include "unordered_set"
#include "unordered_map"

using namespace std;

template <typename KeyType, typename ValueType>
class IRelationshipReader {
public:
    virtual bool isEmpty() = 0;
    virtual unordered_map<KeyType, unordered_set<ValueType>> getKeyValueRelationships() = 0;
    virtual unordered_map<ValueType, unordered_set<KeyType>> getValueKeyRelationships() = 0;
    virtual unordered_set<ValueType> getRelationshipsByKey(KeyType key) = 0;
    virtual unordered_set<ValueType> getRelationshipsByValue(ValueType value) = 0;
    virtual bool hasRelationship(KeyType key, ValueType value) = 0;
};

