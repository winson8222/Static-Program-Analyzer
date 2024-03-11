#pragma once

#include <memory>
#include "pkb/stores/entities/types/StatementStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class StatementWriter: public IEntityWriter<int> {
private:
	std::shared_ptr<StatementStore> statementStore;
public:
	StatementWriter(std::shared_ptr<StatementStore> as);

	bool addEntity(int entity) override;

	void clear() override;

	/**
	 * @brief Inserts a statement into the store.
	 * @param statement The statement being stored.
	 * @return True if the statement is successfully inserted, false otherwise.
	 */
	bool insertStatement(int statement);
};
// ai-gen end
