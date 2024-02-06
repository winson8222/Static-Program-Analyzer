#pragma once

/**
 * @brief Interface for writing entities into a store.
 *
 * @tparam EntityType The type of the entity being managed.
 */
template <typename EntityType>
class IEntityWriter {
public:
    // Adds an entity to the store.
    virtual bool addEntity(EntityType entity) = 0;

    // Clears all entities from the store.
    virtual void clear() = 0;
};
