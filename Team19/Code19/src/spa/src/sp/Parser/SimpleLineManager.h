class SimpleLineManager {
private: 
	int line;
	static const PROGRAM_LINE_NUMBER = -1;

public:
	SimpleLineManager() = default;
	int getLine();
	static int getProgramLineNumber();
	void nextLine();
};