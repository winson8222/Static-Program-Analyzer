#pragma once

#include <utility>

#include "pkb/stores/entities/types/VariableStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

class VariableWriter: public IEntityWriter<std::string> {
private:
    std::shared_ptr<VariableStore> variableStore;
public:
  explicit VariableWriter(std::shared_ptr<VariableStore> vs) {
    variableStore = std::move(vs);
  }

  bool addEntity(std::string entity) override {
    return insertVariable(entity);
  }

  void clear() override {
    variableStore->clear();
  }

  bool insertVariable (std::string &variable) {
    return variableStore->addEntity(variable);
  }
};
