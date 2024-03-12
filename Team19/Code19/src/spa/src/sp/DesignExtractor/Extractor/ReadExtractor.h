#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

/*
* Extracts the read statement from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class ReadExtractor : public IExtractor {
public:
	ReadExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<ReadWriter> readWriter);

	void extract() override;

private:
	std::shared_ptr<ReadWriter> readWriter;
};