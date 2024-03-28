#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include "pkb/PKBWriterManager.h"
#include "sp/AST/ASTNode.h"
#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"
#include "sp/DesignExtractor/Visitor/CFGVisitor.h"

// ai-gen start(copilot, 2, e)
// prompt: GitHub Copilot

/*
* The DesignExtractorFacade class is responsible for extracting all the design abstractions from the AST.
* It is the main entry point for the Design Extractor component.
* It combined all visitors/extractor class from a higher level logical view where we parse a program
* and extract all the design abstractions through visiting them.
* 
* The following are summary of implementation details
* 
• procedure: extracts Procedure_name, StatementList, Uses, Modifies (to be put on contexts)
• stmtLst: extracts Statement, Read, Assign, Print, Call (put on hold for now), While, If, Follows
• stmt
• read (statement): extracts Read, Variable, Modifies.
• print (statement): extracts Print, Variable, Uses.
• assign (statement): extracts Assign, Variable, Constant, Uses, Modifies, Patterns
• call (statement)  // TODO later
• while (statement): extracts While (line number), Variable, Constant, Uses, Modifies, Parent, Follows
• if (statement): extracts If (line num), Variable, Constant, Uses, Modifies, Parent, Follows
• variable: extracts Variable, Uses, Modifies
• constant: extracts Constant, Uses
*/
class DesignExtractorFacade {
public:
    /*
    * Constructor for the DesignExtractorFacade, which takes in the root AST node and the PKBWriterManager.
    */
    DesignExtractorFacade(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);

    /*
    * Extracts all the design abstractions from the AST, starting from the root node which is asserted
    * to be of type PROGRAMS. All the procedures are visited and their design abstractions are extracted.
    * It recursively called all other visitors to extract the design abstractions.
    */
    void extractAll();

private:
    std::shared_ptr<ASTNode> root;
    std::shared_ptr<PKBWriterManager> pkbWriterManager;
    std::vector<std::shared_ptr<CFGNode>> cfgGraphs;

    /*
    * Handles the procedure visitor, which all available designs abstractions from the procedure node.
    */
    void handleProcedureVisitor(std::shared_ptr<ASTNode> procedureNode);

    /*
    * Handles the CFG visitor, which extracts all available designs abstractions from the CFG node.
    */
    void handleCFGVisitor(std::shared_ptr<CFGNode> cfgNode);
};

// ai-gen end
