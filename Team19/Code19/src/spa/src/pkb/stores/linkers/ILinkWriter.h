#pragma once

#include <unordered_set>

// ai-gen start(copilot, 1, e)
// prompt: used copilot
/**
 * @brief Interface for writing links between entities in the store.
 *
 * @tparam LinkerType The type of the entity linking.
 * @tparam LinkedType The type of the entity being linked.
 */
template <typename LinkerType, typename LinkedType>
class ILinkWriter {
public:
    // Adds a link between two entities.
    virtual void addLink(LinkerType linkerEntity, LinkedType linkedEntity) const = 0;

    // Clears all links from the store.
    virtual void clear() = 0;

};
// ai-gen end
