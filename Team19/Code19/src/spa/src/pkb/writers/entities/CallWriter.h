#pragma once

#include <memory>
#include "pkb/stores/entities/types/CallStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class CallWriter: public IEntityWriter<int> {
private:
	std::shared_ptr<CallStore> callStore;
public:
	CallWriter(std::shared_ptr<CallStore> as);

	bool addEntity(int entity) override;

	void clear() override;

	/**
	 * @brief Inserts an "Call" statement into the store.
	 * @param stmtNum The statement number of the call statement.
	 * @return True if the call statement is successfully inserted, false otherwise.
	 */
	bool insertCall(int stmtNum);
};
// ai-gen end
