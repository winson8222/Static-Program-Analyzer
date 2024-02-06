#pragma once

#include "pkb/templates/TemplateMapSet.h"
#include "IRelationshipReader.h"
#include "IRelationshipWriter.h"

using namespace std;

template <typename KeyType, typename ValueType>
class RelationshipStore: public IRelationshipReader<KeyType, ValueType> , public IRelationshipWriter<KeyType, ValueType> {
private:
    TemplateMapSet<KeyType, ValueType> keyToValueMap;
    TemplateMapSet<ValueType, KeyType> valueToKeyMap;
public:
    /**
     * Check if the store is empty
     * @return true if the store is empty, false otherwise
     */
    bool isEmpty() override {
        return keyToValueMap.isEmpty();
    };
    /**
     * Check if the Relationship exists for a given key-value pair
     * @param key
     * @param value
     * @return true if the Relationship exists, false otherwise
     */
    bool hasRelationship(KeyType key, ValueType value) override {
        return keyToValueMap.hasKeyValue(key, value);
    };
    /**
     * Add a relationship to the store
     * @param key
     * @param value
     */
    void addRelationship(KeyType key, ValueType value) override {
        keyToValueMap.addKeyValue(key, value);
        valueToKeyMap.addKeyValue(value, key);
    };
    /**
     * Get all key-value relationships
     * @return map of key-value relationships
     */
    unordered_map<KeyType, unordered_set<ValueType>> getKeyValueRelationships() override {
        return keyToValueMap.getMapSet();
    };
    /**
     * Get all value-key relationships
     * @return map of value-key relationships
     */
    unordered_map<ValueType, unordered_set<KeyType>> getValueKeyRelationships() override {
        return valueToKeyMap.getMapSet();
    };
    /**
     * Get all values related to a given key
     * @param key
     * @return The set of values related to the given key
     */
    unordered_set<ValueType> getRelationshipsByKey(KeyType key) override {
        return keyToValueMap.getValuesByKey(key);
    };
    /**
     * Get all keys related to a given value
     * @param value
     * @return
     */
    unordered_set<KeyType> getRelationshipsByValue(ValueType value) override {
        return valueToKeyMap.getValuesByKey(value);
    };
    /**
     * Clears all stored relationships from the store.
     * This method resets both the key-to-value and value-to-key mappings, effectively
     * removing all relationships.
     */
    void clear() {
        keyToValueMap.clear();
        valueToKeyMap.clear();
    }
};

