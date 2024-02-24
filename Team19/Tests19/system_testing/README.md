# System Tests
This directory contains system tests for the project. 
The system tests run using autotester and take a range of input files specified in the
subdirectory's `queries` and `source` directories. A log file as well as the out.xml file
are produced for each test. The log file is the output in the CLI after the test is executed,
while the out.xml contains the output of the test in XML format.

In the spirit of AI, this README is generated with the assistance of Copilot.

## Milestone 1
```bash
cd m1
chmod +x run_tests.sh
./run_tests.sh
```
