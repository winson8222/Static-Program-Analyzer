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
	WhileWriter(std::shared_ptr<WhileStore> as);

	bool addEntity(int entity) override;

	void clear() override;

	/**
	 * @brief Inserts an "While" statement into the store.
	 * @param stmtNum The statement number of the while statement.
	 * @return True while the while statement is successfully inserted, false otherwise.
	 */
	bool insertWhile(int stmtNum);
};
// ai-gen end
