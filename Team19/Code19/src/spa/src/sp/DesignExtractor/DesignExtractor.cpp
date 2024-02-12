// ai-gen start (gpt, 0, e)
// prompt https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

#include "sp/AST/ASTNode.h"
#include "sp/Utility.h"
#include "DesignExtractor.h"
#include <unordered_set>

DesignExtractor::DesignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriter> pkbWriter)
    : root(std::move(root)), pkbWriter(std::move(pkbWriter)) {
    // No need to assign them in the constructor body
    std::cout << "Initialized" << std::endl;
}

void DesignExtractor::populatePKB() {
    for (const auto& pair : stringInformation) {
        for (auto value : pair.second) {
            if (pair.first == Utility::getASTNodeType(ASTNodeType::CONSTANT)) {
				int intValue = std::stoi(value);
				this->pkbWriter->insertConstant(intValue);
            }
            else if (pair.first == Utility::getASTNodeType(ASTNodeType::CONSTANT)) {
                this->pkbWriter->insertVariable(value);
			}
		}
	}

    for (const auto& pair : intInformation) {
        for (auto value : pair.second) {
            if (pair.first == Utility::getASTNodeType(ASTNodeType::CALL)) {
				this->pkbWriter->insertCall(value);
			}
            else if (pair.first == Utility::getASTNodeType(ASTNodeType::PRINT)) {
				this->pkbWriter->insertPrint(value);
			}
            else if (pair.first == Utility::getASTNodeType(ASTNodeType::READ)) {
				this->pkbWriter->insertRead(value);
			}
            else if (pair.first == Utility::getASTNodeType(ASTNodeType::ASSIGN)) {
				this->pkbWriter->insertAssign(value);
			}
            else if (pair.first == Utility::getASTNodeType(ASTNodeType::IF_ELSE_THEN)) {
				this->pkbWriter->insertIf(value);
			}
            else if (pair.first == Utility::getASTNodeType(ASTNodeType::WHILE)) {
				this->pkbWriter->insertWhile(value);
			}
        }
    }
    std::cout << "PKB Populated\n" << std::endl;
}

/*
For references
std::shared_ptr<ASTNode> parseProcedure();
std::shared_ptr<ASTNode> parseStmtLst();
std::shared_ptr<ASTNode> parseStmt();
std::shared_ptr<ASTNode> parseRead();
std::shared_ptr<ASTNode> parsePrint();
std::shared_ptr<ASTNode> parseCall();
*/

void DesignExtractor::extractAll() {
	// Implementation of extractAll method goes here
	extractFollows();
	extractFollowsStar();
	extractParents();
	extractParentsStar();
	extractUses();
	extractModifies();

    this->stringInformation[Utility::getDesignType(ASTNodeType::PROCEDURE)] = extractProcedures();

    this->intInformation[Utility::getDesignType(ASTNodeType::ASSIGN)] = extractAssigns();
    this->intInformation[Utility::getDesignType(ASTNodeType::IF_ELSE_THEN)] = extractIf();
    this->intInformation[Utility::getDesignType(ASTNodeType::WHILE)] = extractWhiles();
    this->intInformation[Utility::getDesignType(ASTNodeType::CALL)] = extractCall();
    this->intInformation[Utility::getDesignType(ASTNodeType::READ)] = extractRead();
    this->intInformation[Utility::getDesignType(ASTNodeType::PRINT)] = extractPrint();

    this->intInformation[Utility::getDesignType(ASTNodeType::STATEMENT_LIST)] = extractStatements();

    this->stringInformation[Utility::getDesignType(ASTNodeType::CONSTANT)] = extractConstants();
    this->stringInformation[Utility::getDesignType(ASTNodeType::VARIABLE)] = extractVariables();

    std::cout << "Information Extracted\n" << std::endl;
}

void DesignExtractor::entityRecursiveExtractor(const std::shared_ptr<ASTNode>& node, std::vector<ASTNode>& entities, ASTNodeType type) {
    if (node->type == type) {
        // If it's a variable node, add it to the set
        entities.push_back(*node);
    }
    // Recursively traverse children
    for (const auto& child : node->children) {
        entityRecursiveExtractor(child, entities, type);
    }
}


void DesignExtractor::statementRecursiveExtractor(const std::shared_ptr<ASTNode>& node, std::vector<ASTNode>& statements, ASTNodeType type) {
    if (node->type == type) {
        // If it's a variable node, add it to the set
        statements.push_back(*node);
    }
    // Recursively traverse children
    for (const auto& child : node->children) {
        entityRecursiveExtractor(child, statements, type);
    }
}

void DesignExtractor::procedureRecursiveExtractor(const std::shared_ptr<ASTNode>& node, std::vector<ASTNode>& procedures) {

}


// Relations

void DesignExtractor::extractFollows() {
    // Implementation of extractFollows method goes here
}

void DesignExtractor::extractFollowsStar() {
    // Implementation of extractFollowsStar method goes here
}

void DesignExtractor::extractParents() {
    // Implementation of extractParents method goes here
}

void DesignExtractor::extractParentsStar() {
    // Implementation of extractParentsStar method goes here
}

void DesignExtractor::extractUses() {
    // Implementation of extractUses method goes here
}

void DesignExtractor::extractModifies() {
    // Implementation of extractModifies method goes here
}

// Programs

std::unordered_set<std::string> DesignExtractor::extractProcedures() {
    // Implementation of extractProcedures method goes here
    return std::unordered_set<std::string>();
}

// Statements

std::unordered_set<int> DesignExtractor::extractAssigns() {
    // Implementation of extractAssigns method goes here
    return std::unordered_set<int>();
}

std::unordered_set<int> DesignExtractor::extractStatements() {
    // Implementation of extractStatements method goes here
    std::unordered_set<int> allStatements;
    
    std::unordered_set<int> assigns = this->intInformation[Utility::getDesignType(ASTNodeType::ASSIGN)];
    std::unordered_set<int> ifs = this->intInformation[Utility::getDesignType(ASTNodeType::IF_ELSE_THEN)];
    std::unordered_set<int> whiles = this->intInformation[Utility::getDesignType(ASTNodeType::WHILE)];
    std::unordered_set<int> calls = this->intInformation[Utility::getDesignType(ASTNodeType::CALL)];
    std::unordered_set<int> reads = this->intInformation[Utility::getDesignType(ASTNodeType::READ)];
    std::unordered_set<int> prints = this->intInformation[Utility::getDesignType(ASTNodeType::PRINT)];

    allStatements.insert(assigns.begin(), assigns.end());
    allStatements.insert(ifs.begin(), ifs.end());
    allStatements.insert(whiles.begin(), whiles.end());
    allStatements.insert(calls.begin(), calls.end());
    allStatements.insert(reads.begin(), reads.end());
    allStatements.insert(prints.begin(), prints.end());
    return allStatements;
}

std::unordered_set<int> DesignExtractor::extractIf() {
    // Implementation of extractIf method goes here
    return std::unordered_set<int>();
}

std::unordered_set<int> DesignExtractor::extractWhiles() {
    // Implementation of extractWhiles method goes here
    return std::unordered_set<int>();
}

std::unordered_set<int> DesignExtractor::extractCall() {
    // Implementation of extractCall method goes here
    std::unordered_set<int> callStatements;

    std::vector<ASTNode> prints;
    statementRecursiveExtractor(root, prints, ASTNodeType::CALL);

    for (auto node : prints) {
        callStatements.insert(node.lineNumber);
    }

    return callStatements;
}

std::unordered_set<int> DesignExtractor::extractRead() {
    // Implementation of extractRead method goes here
    std::unordered_set<int> readStatements;

    std::vector<ASTNode> prints;
    statementRecursiveExtractor(root, prints, ASTNodeType::READ);

    for (auto node : prints) {
        readStatements.insert(node.lineNumber);
    }

    return readStatements;
}

std::unordered_set<int> DesignExtractor::extractPrint() {
    // Implementation of extractPrint method goes here
    std::unordered_set<int> printStatements;

    std::vector<ASTNode> prints;
    statementRecursiveExtractor(root, prints, ASTNodeType::PRINT);

    for (auto node : prints) {
        printStatements.insert(node.lineNumber);
    }

    return printStatements;
}

// Entities

std::unordered_set<std::string> DesignExtractor::extractVariables() {
    // Recursive function to traverse the AST and extract variables
    // Implementation of extractVariablesRecursive method goes here
    std::vector<ASTNode> variables;
    entityRecursiveExtractor(root, variables, ASTNodeType::VARIABLE);

    std::unordered_set<std::string> variableNames;
    for (auto node : variables) {
		variableNames.insert(node.value);
	}

	return variableNames;
}


std::unordered_set<std::string> DesignExtractor::extractConstants() {
    // Implementation of extractConstants method goes here
    std::vector<ASTNode> constants;
    entityRecursiveExtractor(root, constants, ASTNodeType::CONSTANT);

    std::unordered_set<std::string> constantValues;
    for (auto node : constants) {
        constantValues.insert(node.value);
    }

    return constantValues;
}