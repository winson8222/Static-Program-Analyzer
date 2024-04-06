#pragma once

#include "qps/parser/clauses/Clause.h"


struct WithClause : public Clause {
private:



public:
    ~WithClause() override = default;
    std::string getTypeName() const override {
        return "WithClause";
    }
    std::unordered_set<std::string> getAllSynonyms() const override;
    static bool isSynonym(std::string& ref) ;
    std::string extractSynonym(std::string& ref) const;



};
