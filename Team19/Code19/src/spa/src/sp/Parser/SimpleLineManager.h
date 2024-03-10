
class SimpleLineManager {
private: 
	int line;
	static const int PROGRAM_LINE_NUMBER = -1;

public:
	SimpleLineManager();
	int getLine();
	void nextLine();
	static int getProgramLineNumber();
};