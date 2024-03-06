#include <memory>
#include "PKB.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class PKBCacheManager {
private:
	std::shared_ptr<PKB> pkb;
public:
	explicit PKBCacheManager(const std::shared_ptr<PKB>& pkb): pkb(pkb) {}

	void populateCache() {
		pkb->getNextTStore()->populateNextTStore(pkb->getNextStore());
		// TODO: Populate Affects
	}
	void clearCache() {
		pkb->getNextTStore()->clear();
		// TODO: Clear Affects
	}
};
// ai-gen end
