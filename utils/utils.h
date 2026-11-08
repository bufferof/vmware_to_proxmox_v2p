#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <optional>
#include <shobjidl.h>
#include <initializer_list>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>

std::wstring SelectFolder();
std::string WStringToString(const std::wstring& wstr);
std::wstring SelectFile(std::initializer_list<COMDLG_FILTERSPEC> filters);
std::vector<std::wstring> findFiles(const std::wstring& folder, const std::wstring& extension);
std::string readFile(std::wstring filePath);
std::unordered_map<std::string, std::string> makeXmlToHashMap(std::string fileContent);

#endif