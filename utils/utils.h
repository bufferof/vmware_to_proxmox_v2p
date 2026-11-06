#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <optional>

std::string readTxtFile(const std::string& path);
std::wstring SelectFolder();
std::string WStringToString(const std::wstring& wstr);

#endif