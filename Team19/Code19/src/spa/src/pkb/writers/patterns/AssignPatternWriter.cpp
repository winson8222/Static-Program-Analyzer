#include "AssignPatternWriter.h"

AssignPatternWriter::AssignPatternWriter(std::shared_ptr<AssignPatternStore> store) : assignPatternStore(std::move(store)) {}

void AssignPatternWriter::addAssignPattern(int statementNumber, std::string LHS, std::string RHS)  {
	assignPatternStore->addAssignPattern(statementNumber, LHS, RHS);
}

void AssignPatternWriter::clear()  {
	assignPatternStore->clear();
}