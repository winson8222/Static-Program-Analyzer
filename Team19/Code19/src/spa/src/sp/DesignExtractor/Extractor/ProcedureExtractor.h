#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include <iostream>

/*
* Extracts all the procedures from the AST and writes them to the PKB.
* A procedure is defined as a function or a procedure in the source code.
* Documentations for the methods can be found in IExtractor.h
*/
class ProcedureExtractor : public IExtractor {
public:
	ProcedureExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void extract() override;
};