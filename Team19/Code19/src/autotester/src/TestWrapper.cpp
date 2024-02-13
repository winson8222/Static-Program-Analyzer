#include "TestWrapper.h"
using namespace std;
// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
    if (wrapper == 0) wrapper = new TestWrapper;
    return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;
// a default constructor
TestWrapper::TestWrapper() {
    // create any objects here as instance variables of this class
    // as well as any initialization required for your spa program

    pkbManager = std::make_shared<PKBManager>();
    pkbReader = pkbManager->getPKBReader();
    pkbWriter = pkbManager->getPKBWriter();
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {

    // call your parser to do the parsing

	// call your parser to do the parsing
  // ...rest of your code...

  // example code
	std::string x = "x";
	pkbWriter->insertVariable(x);

}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results) {
    // call your evaluator to evaluate the query here
    // ...code to evaluate query...
    Tokenizer tokenizer(query);
    vector<Token> tokens = tokenizer.tokenize();
    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReader, parsingResult);
    std::vector<string> res = evaluator.evaluateQuery();
    for (auto & re : res) {
        results.push_back(re);
    }
    // store the answers to the query in the results list (it is initially empty)
    // each result must be a string.
}