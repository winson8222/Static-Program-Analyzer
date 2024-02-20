#pragma once

#include <utility>

#include "pkb/stores/entities/types/VariableStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
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

  /**
   * @brief Inserts a variable into the store.
   * @param variable The variable to be inserted.
   * @return True if the variable is successfully inserted, false otherwise.
   */
  bool insertVariable (std::string &variable) {
    return variableStore->addEntity(variable);
  }
};
// ai-gen end
