#pragma once

template <typename EntityType>
class IEntityWriter {
public:
    virtual void addEntity(EntityType entity) = 0;
    virtual void clear() = 0;
};
