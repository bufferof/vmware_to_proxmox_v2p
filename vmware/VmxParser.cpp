#include "VmxParser.h"
#include "utils/utils.h"

#include <iostream>
#include <future>

void make_vmconfig(std::string vmx_filepath)
{
	// GET File DATA
	auto readingRawData = std::async(std::launch::async,readTxtFile,vmx_filepath);
	std::string rawData = readingRawData.get();

	std::cout << rawData[0];
}