#pragma once

#include <memory>
#include "pkb/stores/entities/types/ReadStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class ReadWriter: public IEntityWriter<int> {
private:
	std::shared_ptr<ReadStore> readStore;
public:
	ReadWriter(std::shared_ptr<ReadStore> as);

	bool addEntity(int entity) override;

	void clear() override;

	/**
	 * @brief Inserts an "Read" statement into the store.
	 * @param stmtNum The statement number of the read statement.
	 * @return True read the read statement is successfully inserted, false otherwise.
	 */
	bool insertRead(int stmtNum);
};
// ai-gen end
