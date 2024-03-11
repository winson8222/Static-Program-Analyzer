#pragma once

#include <memory>
#include "pkb/stores/entities/types/PrintStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class PrintWriter: public IEntityWriter<int> {
private:
	std::shared_ptr<PrintStore> printStore;
public:
	PrintWriter(std::shared_ptr<PrintStore> as);

	bool addEntity(int entity) override;

	void clear() override;

	/**
	 * @brief Inserts an "Print" statement into the store.
	 * @param stmtNum The statement number of the print statement.
	 * @return True print the print statement is successfully inserted, false otherwise.
	 */
	bool insertPrint(int stmtNum);
};
// ai-gen end
