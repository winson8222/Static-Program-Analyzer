#pragma once

#include <unordered_set>

// ai-gen start(copilot, 1, e)
// prompt: used copilot
/**
 * @brief Interface for reading links between entities in the store.
 *
 * @tparam LinkerType The type of the entity linking.
 * @tparam LinkedType The type of the entity being linked.
 */
template <typename LinkerType, typename LinkedType>
class ILinkReader {
public:
    // Checks if the store is empty.
    virtual bool isEmpty() = 0;

    // Checks if the store contains a given entity.
    virtual bool hasLink(LinkerType linkerEntity, LinkedType linkedEntity) = 0;

    // Retrieves the set of entity linkers for a given linked entity.
    virtual std::unordered_set<LinkerType> getLinker(LinkedType entity) = 0;

    // Retrieves the linked entity for a given linker entity.
    virtual LinkedType getLinked(LinkerType entity) = 0;
};
// ai-gen end
