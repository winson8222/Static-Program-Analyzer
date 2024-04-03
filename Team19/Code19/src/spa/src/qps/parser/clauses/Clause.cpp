#include "Clause.h"

void Clause::calculatePenalties() {
    penalty = 0;
    std::string clauseType = getTypeName();
    int noOfSynonyms = getAllSynonyms().size();
    try {
        int geClauseTypePenalty = clauseTypeToPenaltiesMap.at(clauseType);
        int getSynonymNumbersPenalty = noOfSynonymsToPenaltiesMap.at(noOfSynonyms);
        penalty = geClauseTypePenalty + getSynonymNumbersPenalty;
        if (clauseType == "SuchThatClause") {
            Token relationshipToken = getRelationship();
            TokenType relationshipType = relationship.getType();
            penalty += suchThatTypeToPenaltiesMap.at(relationshipType);
        }

    } catch (const std::out_of_range& e) {
        throw std::invalid_argument("Invalid clause type or number of synonyms to calculate penalty.");
    }

}

int Clause::getPenalty() {
    if (penalty) {
        return penalty;
    } else {
        calculatePenalties();
        return penalty;
    }
}
