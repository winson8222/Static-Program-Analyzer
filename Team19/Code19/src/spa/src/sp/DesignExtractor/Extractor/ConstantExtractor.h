#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include <stdexcept>

/*
* ConstantExtractor is responsible for extracting constant information from the AST
* This class is a subclass of IExtractor and implements the extract method from it.
* Documentations for the class methods can be found in the IExtractor class.
*/
class ConstantExtractor : public IExtractor {
public:
	explicit ConstantExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {
		if (root->type != ASTNodeType::CONSTANT) {
			throw std::invalid_argument("VariableExtractor: root is not of type VARIABLE");
		}
	}

	void extract() override;

private:
	/*
	* Due to the value stored on token objects and on the AST trees, we could only
	* store strings of the program, hence, a conversion method is required to convert
	* the given value to integer - this is also a good sanity check for parsing errors.
	*/
	int stringToInt(const std::string& str);
};