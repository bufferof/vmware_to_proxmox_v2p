#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <optional>
#include <shobjidl.h>
#include <initializer_list>
#include <vector>

std::string readTxtFile(const std::string& path);
std::wstring SelectFolder();
std::string WStringToString(const std::wstring& wstr);
std::wstring SelectFile(std::initializer_list<COMDLG_FILTERSPEC> filters);
std::vector<std::wstring> findFiles(const std::wstring& folder, const std::wstring& extension);

#endif