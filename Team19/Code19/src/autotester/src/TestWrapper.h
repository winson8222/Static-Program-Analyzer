#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H
#include <string>
#include <iostream>
#include <list>
#include <memory>

// include your other headers here
#include "AbstractWrapper.h"
#include "pkb/PKBManager.h"
#include "qps/Evaluator/QueryEvaluator.h"
#include "qps/Parser/QueryParser.h"
#include "sp/SourceProcessor.h"


class TestWrapper : public AbstractWrapper {
    //private:
    //    shared_ptr<PKBManager> pkbManager;
    //    shared_ptr<PKB> pkb;
    //    shared_ptr<PKBWriter> pkbWriter;
    // shared_ptr<PKBReader> pkbReader;
private:
    std::shared_ptr<PKBManager> pkbManager;
    std::shared_ptr<PKBReaderManager> pkbReaderManager;
    std::shared_ptr<PKBWriterManager> pkbWriterManager;

public:
    // default constructor
    TestWrapper();

    // destructor
    ~TestWrapper();

    // method for parsing the SIMPLE source
    virtual void parse(std::string filename);

    // method for evaluating a query
    virtual void evaluate(std::string query, std::list<std::string>& results);
};
#endif
