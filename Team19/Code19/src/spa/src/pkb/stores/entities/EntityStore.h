#pragma once

#include "IEntityReader.h"
#include "IEntityWriter.h"

template <typename EntityType>
class EntityStore: public IEntityReader<EntityType>, public IEntityWriter<EntityType> {

};
