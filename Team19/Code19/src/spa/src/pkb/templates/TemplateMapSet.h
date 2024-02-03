#pragma once

#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 * @brief Template class for key-set of values store.
 *
 * @tparam KeyType Type of keys in the TemplateMapSet.
 * @tparam ValueType Type of values in the TemplateMapSet.
 */
template <typename KeyType, typename ValueType>
class TemplateMapSet {
private:
    unordered_map<KeyType, unordered_set<ValueType>> map;
public:
    /**
     * @brief Construct an empty TemplateMapSet.
     */
    TemplateMapSet();

    /**
     * @brief Get all values in the TemplateMapSet.
     *
     * @return Map of all key-values in the TemplateMapSet.
     */
    unordered_map<KeyType, unordered_set<ValueType>> getMapSet();

    /**
     * @brief Get all keys in the TemplateMapSet.
     *
     * @return Set of all keys in the TemplateMapSet.
     */
    unordered_set<KeyType> getKeys();

    /**
     * @brief Get all values in the TemplateMapSet.
     *
     * @return Set of all values in the TemplateMapSet.
     */
    unordered_set<ValueType> getValues();

    /**
     * @brief Get the set of values associated with the given key.
     *
     * @param key Key to search for.
     * @return Set of values associated with the given key.
     */
    unordered_set<ValueType> getValuesByKey(KeyType key);

    /**
     * @brief Check if the given key exists in the TemplateMapSet.
     *
     * @param key Key to search for.
     * @return True if the key exists in the TemplateMapSet, false otherwise.
     */
    bool hasKey(KeyType key);

    /**
     * @brief Check if the given value exists in the TemplateMapSet for a given key.
     *
     * @param key Key to search for.
     * @param value Value to search for.
     * @return True if the value exists in the TemplateMapSet, false otherwise.
     */
    bool hasKeyValue(KeyType key, ValueType value);

    /**
     * @brief Add a key-value pair to the TemplateMapSet.
     *
     * @param key Key to add.
     * @param value Value to add.
     */
    void addKeyValue(KeyType key, ValueType value);

    /**
     * @brief Remove the key-value pair associated with the given key from the TemplateMapSet.
     *
     * @param key Key to remove.
     */
    void remove(KeyType key);

    /**
     * @brief Clear all key-value pairs from the TemplateMapSet.
     */
    void clear();
};

/**
 * Default implementations for TemplateMapSet's methods.
 */
template <typename KeyType, typename ValueType>
TemplateMapSet<KeyType, ValueType>::TemplateMapSet() {}

template <typename KeyType, typename ValueType>
unordered_map<KeyType, unordered_set<ValueType>> TemplateMapSet<KeyType, ValueType>::getMapSet() {
    return this->map;
}

template <typename KeyType, typename ValueType>
unordered_set<KeyType> TemplateMapSet<KeyType, ValueType>::getKeys() {
    unordered_set<KeyType> keys;
    for (auto const& pair : this->map) {
        keys.insert(pair.first);
    }
    return keys;
}

template <typename KeyType, typename ValueType>
unordered_set<ValueType> TemplateMapSet<KeyType, ValueType>::getValues() {
    unordered_set<ValueType> values;
    for (auto const& pair : this->map) {
        for (auto const& value : pair.second) {
            values.insert(value);
        }
    }
    return values;
}

template <typename KeyType, typename ValueType>
unordered_set<ValueType> TemplateMapSet<KeyType, ValueType>::getValuesByKey(KeyType key) {
    return this->map[key];
}

template <typename KeyType, typename ValueType>
bool TemplateMapSet<KeyType, ValueType>::hasKey(KeyType key) {
    return this->map.find(key) != this->map.end();
}

template <typename KeyType, typename ValueType>
bool TemplateMapSet<KeyType, ValueType>::hasKeyValue(KeyType key, ValueType value) {
    return this->map[key].find(value) != this->map[key].end();
}

template <typename KeyType, typename ValueType>
void TemplateMapSet<KeyType, ValueType>::addKeyValue(KeyType key, ValueType value) {
    this->map[key].insert(value);
}

template <typename KeyType, typename ValueType>
void TemplateMapSet<KeyType, ValueType>::remove(KeyType key) {
    this->map.erase(key);
}

template <typename KeyType, typename ValueType>
void TemplateMapSet<KeyType, ValueType>::clear() {
    this->map.clear();
}
