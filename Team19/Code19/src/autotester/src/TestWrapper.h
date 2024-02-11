#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>

// include your other headers here
#include "AbstractWrapper.h"
#include "pkb/PKBManager.h"

class TestWrapper : public AbstractWrapper {
//private:
//    shared_ptr<PKBManager> pkbManager;
//    shared_ptr<PKB> pkb;
//    shared_ptr<PKBWriterManager> pkbWriter;
    shared_ptr<PKBReaderManager> pkbReader;
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
