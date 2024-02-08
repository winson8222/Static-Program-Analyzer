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
  pkbManager = make_shared<PKBManager>();
  pkb = pkbManager->getPKB();
  pkbWriter = pkbManager->getPKBWriter();
  pkbReader = pkbManager->getPKBReader();
  pkbWriter->insertVariable("x");
  unordered_set<string> stres = pkbReader->getAllVariables();
  for (const auto& elem: stres) {
      /* ... process elem ... */
      cout << elem << endl;
  }
  cout << "trial1" << endl;
  pkbWriter->insertVariable("y");
  stres = pkbReader->getAllVariables();
  for (const auto& elem: stres) {
    /* ... process elem ... */
    cout << elem << " ";
  }
  cout << endl;
  cout << "trial2" << endl;
  cout << "trial3" << endl;

  pkbWriter->insertFollows(1, 5);
  std::unordered_set<int> res = pkbReader->getPostFollows(1);
  for (const auto& elem: res) {
    /* ... process elem ... */
    cout << elem << endl;
    cout << "trial4" << endl;
  }
  res = pkbReader->getPreFollows(5);
    for (const auto& elem: res) {
        /* ... process elem ... */
        cout << elem << endl;
        cout << "trial5" << endl;
    }


}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your parser to do the parsing
  // ...rest of your code...
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}
