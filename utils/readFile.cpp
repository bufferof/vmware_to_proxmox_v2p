#include "utils.h"

#include <fstream>
#include <sstream>

std::string readTxtFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open()) return "";

	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}