# System Tests
This directory contains system tests for the project. 
The system tests run using autotester and take a range of input files specified in the
subdirectory's `queries` and `source` directories. A log file as well as the out.xml file
are produced for each test. The log file is the output in the CLI after the test is executed,
while the out.xml contains the output of the test in XML format.

Note also that due to our cross-platform developmental nature, there are two ways to run
that are corresponding to the two platforms we are developing on. The first is the `run_tests.sh`
and the second one is 'window_test.ps1'. The former is for Unix-based systems, while the latter
is for Windows-based systems, but they generally did the same thing.

In the spirit of AI, this README is generated with the assistance of Copilot and ChatGPT

## Milestone 1

1. For Mac:
```bash
cd m1
chmod +x run_tests.sh
./run_tests.sh
```

2. For Window:
```
cd m1
.\window_test.ps1
```