#include "DesignExtractorFacade.h"

// error thrown if pkbWriterManager is null
DesignExtractorFacade::DesignExtractorFacade(std::shared_ptr<ASTNode> root, 
		std::shared_ptr<PKBWriterManager> pkbWriterManager) : root(root), pkbWriterManager(pkbWriterManager) {
	if (pkbWriterManager == nullptr) {
		throw std::runtime_error("ERROR: PKBWriterManager is null!");
	}
	if (root->type != ASTNodeType::PROGRAMS) {
		throw std::runtime_error("ERROR: This is not the start node!");
	}
}

// error thrown if root is not a program node or if any of the children of root is not a procedure node
// this error is expected from the requirements of SPA
void DesignExtractorFacade::extractAll() {
	std::vector<ProcedureVisitor> listOfProcedure;
	for (auto& procs : root->children) {
		if (procs->type != ASTNodeType::PROCEDURE) {
			throw std::runtime_error("ERROR: This is not a procedure node!");
		}	
		ProcedureVisitor procedureVisitor(procs, pkbWriterManager);
		listOfProcedure.push_back(procedureVisitor);
	}

	for (auto& procedureVisitor : listOfProcedure) {
		if (procedureVisitor.checkIfVisited()) continue;
		procedureVisitor.visit();
		procedureVisitor.setIsVisited();
	}
}