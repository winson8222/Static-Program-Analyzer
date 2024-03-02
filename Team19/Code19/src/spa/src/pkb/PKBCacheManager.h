#include <memory>
#include "PKB.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class PKBCacheManager {
private:
	std::shared_ptr<PKB> pkb;
public:
	explicit PKBCacheManager(const std::shared_ptr<PKB>& pkb): pkb(pkb) {}

	void clearCache() {
		pkb->getNextTStore()->clear();
	}
};
// ai-gen end
