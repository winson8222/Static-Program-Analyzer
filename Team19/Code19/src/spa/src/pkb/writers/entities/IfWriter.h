#pragma once

#include <memory>
#include "pkb/stores/entities/types/IfStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class IfWriter: public IEntityWriter<int> {
private:
	std::shared_ptr<IfStore> ifStore;
public:
	IfWriter(std::shared_ptr<IfStore> as);

	bool addEntity(int entity) override;

	void clear() override;

	/**
	 * @brief Inserts an "If" statement into the store.
	 * @param stmtNum The statement number of the if statement.
	 * @return True if the if statement is successfully inserted, false otherwise.
	 */
	bool insertIf(int stmtNum);
};
// ai-gen end
