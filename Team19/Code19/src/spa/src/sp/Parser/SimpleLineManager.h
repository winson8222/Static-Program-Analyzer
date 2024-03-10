/**
* @brief Abstraction that handles the counting of line numbers during the Simple code parsing process.
*/
class SimpleLineManager {
private:
	int lineNumber;
	static const int PROGRAM_LINE_NUMBER = -1;

public:
	/**
	* @brief default constructor for creating a line manager.
	*/
	SimpleLineManager();

	/**
	* @brief Gets the current Simple program line number
	*/
	int getLine();

	/**
	* @brief Set to the next line of Simple program
	*/
	void nextLine();

	/**
	* @brief Gets an invalid line number, which is assigned to tokens that do not need a valid line number.
	*/
	static int getProgramLineNumber();
};
