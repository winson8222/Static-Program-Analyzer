#pragma once

#include <memory>
#include "pkb/PKB.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class PKBCacheManager {
private:
    std::shared_ptr<PKB> pkb;
    bool affectsPopulated = false;
    bool nextTPopulated = false;
public:
    explicit PKBCacheManager(const std::shared_ptr<PKB>& pkb): pkb(pkb) {}

    void populateCache() {
        pkb->getNextTStore()->populateNextTStore();
        pkb->getAffectsStore()->populateAffectsStore();
    }

    void populateNextTCache() {
        if (!nextTPopulated) {
            pkb->getNextTStore()->populateNextTStore();
            nextTPopulated = true;
        }
    }

    void populateAffectsCache() {
        if (!affectsPopulated) {
            pkb->getAffectsStore()->populateAffectsStore();
            affectsPopulated = true;
        }
    }
    void clearCache() {
        pkb->getNextTStore()->clear();
        pkb->getAffectsStore()->clear();
    }
};
// ai-gen end
