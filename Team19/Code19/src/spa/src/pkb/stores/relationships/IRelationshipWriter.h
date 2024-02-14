#pragma once

/**
 * @brief Interface for writing key-value relationships.
 *
 * This interface defines the contract for a component that can add relationships
 * between keys and values. Each key can be associated with multiple values.
 *
 * @tparam KeyType The data type of the key in the relationship.
 * @tparam ValueType The data type of the value in the relationship.
 */
template <typename KeyType, typename ValueType>
class IRelationshipWriter {
public:
    /**
     * Adds a relationship between a key and a value.
     * If the key already exists, the value is added to the existing set of values.
     * If the key does not exist, it is created and associated with the value.
     *
     * @param key The key to associate the value with.
     * @param value The value to be associated with the key.
     */
    virtual void addRelationship(KeyType key, ValueType value) = 0;

    // Clears all entities from the store.
    virtual void clear() = 0;
};
