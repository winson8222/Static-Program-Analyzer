#pragma once

#include <memory>

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/NextStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class NextWriter : public IRelationshipWriter<int, int> {
private:
	std::shared_ptr<NextStore> nextStore;

public:
	explicit NextWriter(std::shared_ptr<NextStore> store);

	void addRelationship(int precedingStmt, int followingStmt) override;

	void clear() override;
	// Custom methods
	/**
	 * @brief Adds a "Next" relationship between a preceding statement and a following statement.
	 * @param stmtNum The statement number of the preceding statement.
	 * @param nextStmt The statement number of the next statement.
	 */
	void addNext(int stmtNum, int nextStmt);
};
// ai-gen end
