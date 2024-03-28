#pragma once

#include <stdexcept>
#include "sp/DesignExtractor/Extractor/PatternExtractor/IPatternExtractor.h"

/*
* Extracts the pattern statement from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class IfsPatternExtractor : public IPatternExtractor {
public:
	IfsPatternExtractor(
		std::shared_ptr<ASTNode> root,
		std::shared_ptr<ASTNode> variable,
		std::shared_ptr<IfPatternWriter> ifWriter);

	void extract() override;
private:
	std::shared_ptr<IfPatternWriter> ifWriter;
};
