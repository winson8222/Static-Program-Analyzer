#include <string>

/**
 * @brief Represents a file processor which takes in file names as string and processes them.
 */
class FileProcessor {
public:
	/**
	* @brief Reads the content of a file and returns it as a string.
	*
	* @param filename The name of the file to be read.
	* @return The content of the file as a string.
	*/
	static std::string readFileToString(const std::string& filename);

	/**
	* @brief Assert that a file exists.
	*/
	static void assertFileExists(const std::string& filename);
};
