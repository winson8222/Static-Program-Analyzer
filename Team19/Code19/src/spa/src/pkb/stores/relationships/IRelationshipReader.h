#pragma once

#include <unordered_set>
#include <unordered_map>

/**
 * @brief Interface for reading key-value relationships.
 *
 * This interface defines the contract for a component that can read relationships
 * between keys and values, where a single key may be associated with multiple values,
 * and vice versa.
 *
 * @tparam KeyType The data type of the key in the relationship.
 * @tparam ValueType The data type of the value in the relationship.
 */
template <typename KeyType, typename ValueType>
class IRelationshipReader {
public:
    /**
     * Checks if there are any relationships stored.
     * @return true if no relationships exist, false otherwise.
     */
    virtual bool isEmpty() = 0;

    /**
     * Retrieves all relationships in a map where each key is associated with a set of values.
     * @return A map of keys to sets of values.
     */
    virtual unordered_map<KeyType, unordered_set<ValueType>> getKeyValueRelationships() = 0;

    /**
     * Retrieves all relationships in a map where each value is associated with a set of keys.
     * @return A map of values to sets of keys.
     */
    virtual unordered_map<ValueType, unordered_set<KeyType>> getValueKeyRelationships() = 0;

    /**
     * Retrieves all values associated with a given key.
     * @param key The key to retrieve values for.
     * @return A set of values associated with the key.
     */
    virtual unordered_set<ValueType> getRelationshipsByKey(KeyType key) = 0;

    /**
     * Retrieves all keys associated with a given value.
     * @param value The value to retrieve keys for.
     * @return A set of keys associated with the value.
     */
    virtual unordered_set<ValueType> getRelationshipsByValue(ValueType value) = 0;

    /**
     * Checks if a specific relationship exists between a key and a value.
     * @param key The key part of the relationship to check.
     * @param value The value part of the relationship to check.
     * @return true if the relationship exists, false otherwise.
     */
    virtual bool hasRelationship(KeyType key, ValueType value) = 0;
};
