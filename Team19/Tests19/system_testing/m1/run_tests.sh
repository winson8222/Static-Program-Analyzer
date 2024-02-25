echo "[System Test] Running all tests for Milestone 1";
EXIT_CODE="0";

for file in source/*_source.txt; do
  # shellcheck disable=SC2001
  test_name=$(echo "$file" | sed 's|.*/\(.*\)_source\.txt$|\1|') # regex generated with aid of ChatGPT
  echo "[System Test] Running Test: $test_name"
  ../../../Code19/cmake-build-debug/src/autotester/autotester "$file" queries/"$test_name"_queries.txt outputs/"$test_name"_output.xml > logs/log_"$test_name".txt

	if [ "$?" != 0 ] # Check if the test caused the autotester to crash
	then
	    EXIT_CODE="1";
	else
		head -1 logs/log_"$test_name".txt;
		FILENAME=outputs/"$test_name"_output.xml;
		QUERIES=$(grep -o '</query>' "$FILENAME" | wc -l);
		PASSES=$(grep -o '<passed/>' "$FILENAME" | wc -l);
		FAILS=$(grep -o '</failed>' "$FILENAME" | wc -l);
		echo "[System Test] Queries: $QUERIES; Passes: $PASSES; Fails: $FAILS"

		if [ "$QUERIES" != "$PASSES" ]
		then
			EXIT_CODE="2";
		fi
	fi
done

exit $EXIT_CODE
