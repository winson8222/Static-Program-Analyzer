#pragma once

#include <memory>
#include "pkb/stores/entities/types/WhileStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class WhileWriter: public IEntityWriter<int> {
private:
    std::shared_ptr<WhileStore> whileStore;
public:
    explicit WhileWriter(std::shared_ptr<WhileStore> ws) : whileStore(std::move(ws)) {}

    bool addEntity(int entity) override {
      return insertWhile(entity);
    }

    void clear() override {
      whileStore->clear();
    }

    /**
     * @brief Inserts a while statement into the PKB.
     * @param stmtNum The statement number of the while statement.
     * @return True if the while statement is successfully inserted, false otherwise.
     */
    bool insertWhile(int stmtNum) {
      return whileStore->addEntity(stmtNum);
    }
};
// ai-gen end
