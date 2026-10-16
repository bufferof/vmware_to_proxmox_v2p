#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <optional>

std::string readTxtFile(const std::string& path);
std::optional<std::wstring> readFilePath();
std::string WStringToString(const std::wstring& wstr);

#endif