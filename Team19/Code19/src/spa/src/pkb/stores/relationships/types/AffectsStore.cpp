#include "AffectsStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
AffectsStore::AffectsStore(
        std::shared_ptr<AssignStore> assignStore,
        std::shared_ptr<NextStore> nextStore,
        std::shared_ptr<UsesSStore> usesSStore,
        std::shared_ptr<ModifiesSStore> modifiesSStore
) : assignStore(std::move(assignStore)),
    nextStore(std::move(nextStore)),
    usesSStore(std::move(usesSStore)),
    modifiesSStore(std::move(modifiesSStore)) {}

void AffectsStore::populateAffectsStore() {
    std::unordered_set<int> allAssigns = assignStore->getAllEntities();
    for (int assign : allAssigns) {
        AffectsStore::populateAffectByStatement(assign);
    }
}

void AffectsStore::populateAffectByStatement(int statement) {
    std::unordered_set<int> nextStatements = nextStore->getRelationshipsByKey(statement);
    std::queue<int> queue;
    std::string assignedVariable = *(modifiesSStore->getRelationshipsByKey(statement).begin());
    for (int nextStatement : nextStatements) queue.push(nextStatement);
    AffectsStore::populateFromQueue(statement, queue, assignedVariable);
}

void AffectsStore::populateFromQueue(int statement, std::queue<int> &queue, const std::string &assignedVariable) {
    std::unordered_set<int> visited;
    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();
        if (visited.find(current) != visited.end()) continue;
        visited.insert(current);
        if (AffectsStore::handleAddAffects(statement, current, assignedVariable)) continue;
        std::unordered_set<int> newNextStatements = nextStore->getRelationshipsByKey(current);
        for (int nextStatement : newNextStatements) queue.push(nextStatement);
    }
}

bool AffectsStore::handleAddAffects(int statement, int current, const std::string& assignedVariable) {
    if (assignStore->contains(current)) {
        std::unordered_set<std::string> usedVariables = usesSStore->getRelationshipsByKey(current);
        if (usedVariables.find(assignedVariable) != usedVariables.end()) {
            AffectsStore::addRelationship(statement, current);
        }
        return assignedVariable == *(modifiesSStore->getRelationshipsByKey(current).begin());
    } else if (modifiesSStore->hasRelationship(current, assignedVariable)) {
		return true;
	}
    return false;
}
// ai-gen end
