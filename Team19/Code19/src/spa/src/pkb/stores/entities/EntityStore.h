#pragma once

#include <unordered_set>
#include "IEntityReader.h"
#include "IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
/**
 * @brief A store that manages a collection of entities of a certain type.
 *
 * @tparam EntityType The type of entities being stored.
 */
template <typename EntityType>
class EntityStore : public IEntityReader<EntityType>, public IEntityWriter<EntityType> {
private:
    std::unordered_set<EntityType> entities;

public:
    // IEntityWriter implementation
    bool addEntity(EntityType entity) override {
        return entities.insert(entity).second;
    }

    void clear() override {
        entities.clear();
    }

    // IEntityReader implementation
    bool isEmpty() const override {
        return entities.empty();
    }

    bool contains(EntityType entity) const override {
        return entities.find(entity) != entities.end();
    }

    std::unordered_set<EntityType> getAllEntities() const override {
        return entities;
    }
};
// ai-gen end
