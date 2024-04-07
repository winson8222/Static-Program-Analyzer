#pragma once

#include "pkb/templates/TemplateMapSet.h"
#include "IRelationshipReader.h"
#include "IRelationshipWriter.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
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
    std::unordered_map<KeyType, std::unordered_set<ValueType>> getKeyValueRelationships() override {
        return keyToValueMap.getMapSet();
    };
    /**
     * Get all value-key relationships
     * @return map of value-key relationships
     */
    std::unordered_map<ValueType, std::unordered_set<KeyType>> getValueKeyRelationships() override {
        return valueToKeyMap.getMapSet();
    };

    /**
     * Get all keys in the store
     * @return set of keys
     */
    std::unordered_set<KeyType> getKeys() override {
        return keyToValueMap.getKeys();
    };

    /**
     * Get all values in the store
     * @return set of values
     */
    std::unordered_set<ValueType> getValues() override {
        return valueToKeyMap.getKeys();
    };

    /**
     * Get all values related to a given key
     * @param key
     * @return The set of values related to the given key
     */
    std::unordered_set<ValueType> getRelationshipsByKey(KeyType key) override {
        return keyToValueMap.getValuesByKey(key);
    };
    /**
     * Get all keys related to a given value
     * @param value
     * @return
     */
    std::unordered_set<KeyType> getRelationshipsByValue(ValueType value) override {
        return valueToKeyMap.getValuesByKey(value);
    };
    /**
     * Clears all stored relationships from the store.
     * This method resets both the key-to-value and value-to-key mappings, effectively
     * removing all relationships.
     */
    void clear() override {
        keyToValueMap.clear();
        valueToKeyMap.clear();
    }

    /**
     * Gets the size of the store
     * @return The number of relationships in the store
    */
    int getSize() override {
        int count = 0;
        for (auto& key : keyToValueMap.getKeys()) {
            count += keyToValueMap.getValuesByKey(key).size();
        }
        return count;
    }

    /**
     * Gets the number of relationships by key.
     * @param key The key to get the number of relationships for.
     * @return The number of relationships for the key.
     */
    int getRelationshipCountByKey(KeyType key) override {
        if (!keyToValueMap.hasKey(key)) {
            return 0;
        }
        return keyToValueMap.getValuesByKey(key).size();
    }

    /**
      * Gets the number of relationships by value.
      * @param value The value to get the number of relationships for.
      * @return The number of relationships for the value.
      */
    int getRelationshipCountByValue(ValueType value) override {
        if (!valueToKeyMap.hasKey(value)) {
            return 0;
        }
        return valueToKeyMap.getValuesByKey(value).size();
    }
};
// ai-gen end
