#pragma once

#include <memory>
#include "pkb/stores/entities/types/VariableStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class VariableWriter: public IEntityWriter<std::string> {
private:
	std::shared_ptr<VariableStore> variableStore;
public:
	VariableWriter(std::shared_ptr<VariableStore> as);

	bool addEntity(std::string entity) override;

	void clear() override;

	/**
	 * @brief Inserts a variable into the store.
	 * @param variable The variable being stored.
	 * @return True if the variable is successfully inserted, false otherwise.
	 */
	bool insertVariable(std::string variable);
};
// ai-gen end
