#include "sp/SourceProcessor.h"
#include <iostream>

SourceProcessor::SourceProcessor(std::string filename, std::shared_ptr<PKBManager> pkbManager) {
    this->pkbManager = pkbManager;
	this->parser = SimpleParser(filename);
    this->root = std::make_shared<ASTNode>();
    std::cout << "File created" << std::endl;
}

void SourceProcessor::reset() {
	this->root = std::make_shared<ASTNode>();
}

void SourceProcessor::parseSIMPLE() {
	// Parse tokens into AST (not implemented)
	this->root = parser.parseProgram();
	std::cout << this->root->toString() << std::endl;
}

void SourceProcessor::buildAST() {
	// Build AST from parsed tokens (not implemented)
	// this->root = ast.build();
}

void SourceProcessor::sampleAST() {
    // hard coded Sample AST for testing purposes
	auto ast1 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "i");
	auto ast2 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 1, Utility::getASTNodeType(ASTNodeType::ASSIGN));
	auto ast3 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1");

	auto ast4 = std::make_shared<ASTNode>(ASTNodeType::WHILE, 2, Utility::getASTNodeType(ASTNodeType::WHILE));
	auto ast5 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 2, "i");
	auto ast6 = std::make_shared<ASTNode>(ASTNodeType::LESSER, 2, Utility::getASTNodeType(ASTNodeType::LESSER));
	auto ast7 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 2, "3");

	auto ast8 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "j");
	auto ast9 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 3, Utility::getASTNodeType(ASTNodeType::ASSIGN));
	auto ast10 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "k");
	auto ast11 = std::make_shared<ASTNode>(ASTNodeType::ADD, 3, Utility::getASTNodeType(ASTNodeType::ADD));
	auto ast12 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 3, "1");

	ast11->addChild(std::move(ast10));
	ast11->addChild(std::move(ast12));
	ast9->addChild(std::move(ast8));
	ast9->addChild(std::move(ast11));

	ast6->addChild(std::move(ast5));
	ast6->addChild(std::move(ast7));
	ast4->addChild(std::move(ast6));
	ast4->addChild(std::move(ast9));

	ast2->addChild(std::move(ast1));
	ast2->addChild(std::move(ast3));

	this->root->addChild(std::move(ast2));
	this->root->addChild(std::move(ast4));

	std::cout << this->root->toString() << std::endl;
}

void SourceProcessor::extractAndPopulate() {
    // Use PKBWriter to insert entities and relationships into PKB
    std::shared_ptr<PKBWriterManager> pkbWriterManager = this->pkbManager->getPKBWriterManager();
	DesignExtractor designExtractor(this->root, pkbWriterManager);
	designExtractor.extractAll();
    designExtractor.populatePKB();
}
