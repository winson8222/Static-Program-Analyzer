#pragma once

#include <memory>
#include "pkb/stores/entities/types/ConstantStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class ConstantWriter: public IEntityWriter<int> {
private:
	std::shared_ptr<ConstantStore> constantStore;
public:
	ConstantWriter(std::shared_ptr<ConstantStore> as);

	bool addEntity(int entity) override;

	void clear() override;

	/**
	 * @brief Inserts a constant into the store.
	 * @param constant The constant being stored.
	 * @return True if the constant is successfully inserted, false otherwise.
	 */
	bool insertConstant(int constant);
};
// ai-gen end
