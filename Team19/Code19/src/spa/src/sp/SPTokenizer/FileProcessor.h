#include <string>

class FileProcessor {
public:
	static std::string readFileToString(const std::string& filename);
	static void assertFileExists(const std::string& filename);
};