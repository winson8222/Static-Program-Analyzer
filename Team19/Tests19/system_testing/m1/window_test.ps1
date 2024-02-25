Write-Host "[System Test] Running all tests for Milestone 1"
$EXIT_CODE = 0

foreach ($file in Get-ChildItem source/*_source.txt) {
    Write-Host "Run test"
    $test_name = ($file.Name -split "_source.txt")[0]  # Extract test name from file name
    Write-Host "[System Test] Running Test: $test_name"
    & ../../../Code19/out/build/x64-Debug/src/autotester/autotester.exe "source/${test_name}_source.txt" "queries/${test_name}_queries.txt" "outputs/${test_name}_output.xml" > "logs/log_${test_name}.txt"
    
    if ($LASTEXITCODE -ne 0) {
        $EXIT_CODE = 1
    }
    else {
        $firstLine = Get-Content "logs/log_${test_name}.txt" -First 1
        Write-Host $firstLine
        $FILENAME = "outputs/${test_name}_output.xml"
        $QUERIES = ((Get-Content $FILENAME) -match '</query>').Count
        $PASSES = ((Get-Content $FILENAME) -match '<passed/>').Count
        $FAILS = ((Get-Content $FILENAME) -match '</failed>').Count
        Write-Host "[System Test] Queries: $QUERIES; Passes: $PASSES; Fails: $FAILS"

        if ($QUERIES -ne $PASSES) {
            $EXIT_CODE = 2
        }
    }
}

exit $EXIT_CODE