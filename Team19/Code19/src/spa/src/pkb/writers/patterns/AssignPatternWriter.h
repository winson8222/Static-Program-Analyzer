#pragma once

#include <memory>

#include "pkb/stores/patterns/assign/IAssignPatternWriter.h"
#include "pkb/stores/patterns/assign/AssignPatternStore.h"

class AssignPatternWriter : public IAssignPatternWriter {
private:
    std::shared_ptr<AssignPatternStore> assignPatternStore;
public:
    explicit AssignPatternWriter(std::shared_ptr<AssignPatternStore> store) : assignPatternStore(std::move(store)) {}

    void addAssignPattern(int statementNumber, std::string LHS, std::string RHS) override {
      assignPatternStore->addAssignPattern(statementNumber, LHS, RHS);
    }

    // Clears all assign patterns from the store.
    void clear() override {
      assignPatternStore->clear();
    }
};
