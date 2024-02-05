#pragma once

#include <unordered_set>

/**
 * @brief Interface for reading entities from a store.
 *
 * @tparam EntityType The type of the entity being managed.
 */
template <typename EntityType>
class IEntityReader {
public:
    // Checks if the store is empty.
    virtual bool isEmpty() const = 0;

    // Checks if the store contains a given entity.
    virtual bool contains(EntityType entity) const = 0;

    // Retrieves all entities from the store.
    virtual std::unordered_set<EntityType> getAllEntities() const = 0;
};
