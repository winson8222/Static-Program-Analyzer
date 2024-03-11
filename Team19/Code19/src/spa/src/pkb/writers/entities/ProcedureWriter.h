#pragma once

#include <memory>
#include "pkb/stores/entities/types/ProcedureStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class ProcedureWriter: public IEntityWriter<std::string> {
private:
	std::shared_ptr<ProcedureStore> procedureStore;
public:
	ProcedureWriter(std::shared_ptr<ProcedureStore> as);

	bool addEntity(std::string entity) override;

	void clear() override;

	/**
	 * @brief Inserts a procedure into the store.
	 * @param procedure The procedure being stored.
	 * @return True if the procedure is successfully inserted, false otherwise.
	 */
	bool insertProcedure(std::string procedure);
};
// ai-gen end
